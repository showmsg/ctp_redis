#include "Logger.h"

#include <time.h>           //strftime
#include <assert.h>
#include <stdarg.h>         //vsnprintf,va_start,va_end
#include <algorithm>        //sort
#include <string.h>

#ifdef WIN32
#include <io.h>             //access, _finddata_t, _findfirst, _findnext
#include <direct.h>         //_mkdir
#include <process.h>        //_beginthread

#define MKDIR(a)            _mkdir((a))
#define PATH_SEPARATER      '\\'
#define usleep(t)           Sleep(t/1000)
#else
#include <unistd.h>         //access
#include <sys/stat.h>       //mkdir
#include <sys/time.h>       //gettimeofday
#include <dirent.h>         //opendir,readdir,closedir
#include <pthread.h>        //pthread_create

#define MKDIR(a)            mkdir((a),0755)
#define PATH_SEPARATER      '/'

#include <sys/syscall.h>    //for pid_t, syscall
pid_t gettid() {  return syscall(SYS_gettid); }
#endif

#define DEFAULT_LOG_SIZE        (10*1024*1024)//10M
#define DEFAULT_MAX_LOG_SPACE   (500*1024*1024)//500M
#define MAX_PATH                512

#define CLEANLOG_SLEEP_TIME     100000  //100ms

#define NEW_LINE                "\r\n"

static const char* s_level_str[] = {"ERROR", "WARNING", "INFO", "TRACE"};

#define FCLOSE(fp)    {if (NULL != fp) {fclose(fp); fp = NULL;}}

bool cmp_file(const file_info& pl, const file_info& pr)
{
    return pl.mtime > pr.mtime; //降序排列,故返回>
}

CLog::CLog(void)
{
    m_log_filename = "app.log";
    m_fp = NULL;
    m_log_level = LOG_LEVEL_INFO;
    m_log_size = DEFAULT_LOG_SIZE;
    m_max_log_space = DEFAULT_MAX_LOG_SPACE;
    m_is_cleaning = false;
}

CLog::~CLog(void)
{
    FCLOSE(m_fp);
}

void CLog::rotate_log()
{
    assert(m_log_filename.length() > 0);

    if (m_fp != NULL)
    {
        fprintf(m_fp, "Rotate log file");
    }

    FCLOSE(m_fp);
	if(get_file_size(m_log_filename.c_str()) > m_log_size)
	{
		rename_file();
	}    

    m_fp = fopen(m_log_filename.c_str(), "wb");
    if (NULL == m_fp)
    {
        fprintf(stderr, "Open log file(%s) fail!\n", m_log_filename.c_str());
    }
}
unsigned long CLog::get_file_size(const char* filename)
{
   struct stat buf; 
   if(stat(filename, &buf)<0) 
   { 
		return 0; 
   } 
   return (unsigned long)buf.st_size; 
}
bool CLog::mk_dir()
{
    assert(m_log_filename.length() > 0);

    char* p_str = (char*)m_log_filename.c_str();
    int len = m_log_filename.find_last_of(PATH_SEPARATER);
    if (string::npos == len) return false;//找不到路径分隔符直接返回

    char dir[MAX_PATH] = {0};
    strncpy(dir, p_str, ++len);

    if (0 != access(dir, 0))
    {
        //创建目录(TODO: "./","../"等相对路径的情况未处理)
        for (int i = 1; i < len; i++)
        {
            if (dir[i] == PATH_SEPARATER)
            {
                dir[i] = '\0';

                if ((0 != access(dir, 0)) && (0 != MKDIR(dir)))
                {//如果目录不存在,且创建失败
                    return false;
                }

                dir[i] = PATH_SEPARATER;
            }
        }
    }

    return true;
}

char* CLog::get_time_str(bool is_write)
{
    time_t now = {0};
    struct tm *ptime = NULL;
    time(&now);
    ptime = localtime(&now);
    memset(m_time_str, 0, sizeof(m_time_str));

    uint32 milisec = 0;
#ifdef WIN32
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    milisec = wtm.wMilliseconds;
#else
    struct timeval tv = {0};
    gettimeofday(&tv, 0);
    milisec = tv.tv_usec/1000;
#endif

    if (is_write)
    {//用来写日志
        sprintf(m_time_str, "%04d%02d%02d-%02d:%02d:%02d.%06ld",
            (1900+ptime->tm_year), (1+ptime->tm_mon), ptime->tm_mday,
            ptime->tm_hour, ptime->tm_min, ptime->tm_sec, milisec);
    }
    else
    {//用来重命名文件
        sprintf(m_time_str, "%04d-%02d-%02d-%02d_%02d_%02d_%06ld",
            (1900+ptime->tm_year), (1+ptime->tm_mon), ptime->tm_mday,
            ptime->tm_hour, ptime->tm_min, ptime->tm_sec, milisec);
    }

    return m_time_str;
}

bool CLog::rename_file()
{
    string new_name = m_log_filename + "-" + get_time_str(false);
    return (0 == rename(m_log_filename.c_str(), new_name.c_str()));
}

int CLog::get_thread_id()
{
#ifdef WIN32
    return GetCurrentThreadId();
#else
    return gettid();
#endif
}

int CLog::writeline(uint level, const char* format_str, ...)
{
    if (m_log_level < level) return 0;
		
    m_lock.lock();
    assert(NULL != m_fp);
    if (ftell(m_fp) >= m_log_size)
    {
        rotate_log();//切换日志写入
        clean_logs();//清除日志
    }

    int write_len = fprintf(m_fp, "[%s-%d][%s]", get_time_str(true), get_thread_id(), s_level_str[level-1]);

    va_list p_list;
    va_start(p_list, format_str);
    write_len += vfprintf(m_fp, format_str, p_list);
    va_end(p_list);
    write_len += fprintf(m_fp, "\n");
    fflush(m_fp);
    m_lock.unlock();

    return write_len;
}

void CLog::clean_logs()
{
    if (!m_is_cleaning)
    {
        m_is_cleaning = true;

#ifdef WIN32
        _beginthread(clean_logs_thread_fun, NULL, this);
#else
        pthread_t pid = 0;
        int ret = pthread_create(&pid, (pthread_attr_t*)0, clean_logs_thread_fun, this);
#endif
    }
}

#ifdef WIN32
void CLog::clean_logs_thread_fun(void* param)
#else
void* CLog::clean_logs_thread_fun(void* param)
#endif
{
    CLog* log_ptr = (CLog*)param;

    file_list files;
    string log_path = log_ptr->get_log_path();
    get_log_files(log_path, files);

    sort(files.begin(), files.end(), cmp_file);

    int count = files.size();

    uint64 sum_size = 0;
    uint64 max_space = log_ptr->get_max_space();
    for (int i = 0; i < count; i++)
    {
        if (sum_size < max_space)
        {
            sum_size += files[i].size;
        }
        else
        {
            unlink(files[i].file_path.c_str());//删除文件
            log_ptr->writeline(LOG_LEVEL_INFO, "delete %s", files[i].file_path.c_str());
            printf("delete %s\n", files[i].file_path.c_str());

            //sleep 100ms，避免删除日志引起CPU升高
            fflush(stdout);
            usleep(CLEANLOG_SLEEP_TIME);
        }
    }

    log_ptr->set_clean_status(false);
}

#ifdef WIN32
bool CLog::get_log_files(const string& log_path, file_list& files)
{
    _finddata_t file_data;
    string file_filter = log_path + "*";
    long handle = _findfirst(file_filter.c_str(), &file_data);

    if (handle == -1L)
    {
        return false;
    }

    file_info info = {"", 0, 0};
    string log_dir = get_log_dir(log_path);

    files.clear();

    do
    {
        info.file_path = log_dir + file_data.name;
        info.size = file_data.size;
        info.mtime = file_data.time_write;
        files.push_back(info);

    } while (_findnext(handle, &file_data) == 0);

    return true;
}
#else
bool CLog::get_log_files(const string& log_path, file_list& files)
{
    string log_dir = get_log_dir(log_path);
    DIR* dir = opendir(log_dir.c_str());
    if (dir == NULL)
    {
        return false;
    }

    files.clear();

    const char* filename = strrchr(log_path.c_str(), PATH_SEPARATER) + 1;
    int name_len = strlen(filename);

    file_info info = {"", 0, 0};
    struct stat st = {0};
    struct dirent* ptr = NULL;
    while ((ptr = readdir(dir)) != NULL)
    {
        if (strncmp(filename, ptr->d_name, name_len) == 0)
        {
            info.file_path = log_dir + ptr->d_name;
            stat(info.file_path.c_str(), &st);
            info.size = st.st_size;
            info.mtime = st.st_mtime;
            files.push_back(info);
        }
    }

    closedir(dir);
}
#endif

string CLog::get_log_dir(const string& log_path)
{
    int pos = log_path.find_last_of(PATH_SEPARATER);
    string dir = log_path.substr(0, pos + 1);

    return dir;
}

//////////////////////////////////////////////////////////////
// Log Factory
//////////////////////////////////////////////////////////////

log_inst    CLogFactory::m_inst_list[MAX_LOG_INSTANCE] = {0};
uint        CLogFactory::m_inst_num = 0;
MutexLock   CLogFactory::m_lock;

CLogFactory::CLogFactory(void)
{
}

CLogFactory::~CLogFactory(void)
{
    free_all_inst();
}

CLog* CLogFactory::get_instance(const char* name)
{
    CLog* plog = NULL;
    for (int i = 0; i < m_inst_num; i++)
    {
        if (0 == strcmp(m_inst_list[i].name, name))
        {
            plog = m_inst_list[i].plog;
            break;
        }
    }

    if ((NULL == plog) && (m_inst_num < MAX_LOG_INSTANCE))
    {
        m_lock.lock();
        plog = new CLog();
        strcpy(m_inst_list[m_inst_num].name, name);
        m_inst_list[m_inst_num].plog = plog;
        m_inst_num++;
        m_lock.unlock();
    }

    return plog;
}

void CLogFactory::free_instance(const char* name)
{
    m_lock.lock();
    for (int i = 0; i < m_inst_num; i++)
    {
        if (m_inst_list[i].name == name)
        {
            delete m_inst_list[i].plog;
            memset(m_inst_list[i].name, 0, sizeof(m_inst_list[i].name));
            m_inst_list[i].plog = NULL;
            break;
        }
    }
    m_lock.unlock();
}

void CLogFactory::free_all_inst()
{
    m_lock.lock();
    for (int i = 0; i < m_inst_num; i++)
    {
        delete m_inst_list[i].plog;
        memset(m_inst_list[i].name, 0, sizeof(m_inst_list[i].name));
        m_inst_list[i].plog = NULL;
    }
    m_lock.unlock();
}

