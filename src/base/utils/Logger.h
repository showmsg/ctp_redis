/*********************************************************************
* Filename: Log.hh
* Abstract: Log Class corss-platform(linux and windows)
*
* Version : 0.1
* Author  : js2854
* Date    : 2013/09/03
**********************************************************************/
#ifndef __Log_h__
#define __Log_h__

#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

#define SINGLE_LOG

#ifdef SINGLE_LOG
//单实例API
#define DEFAULT_MODULE                      "DEFAULT"
#define SET_LOG_NAME(filepath)              CLogFactory::get_instance(DEFAULT_MODULE)->set_log_filepath(filepath)
#define SET_LOG_LEVEL(level)                CLogFactory::get_instance(DEFAULT_MODULE)->set_log_level(level)
#define SET_LOG_SIZE(size)                  CLogFactory::get_instance(DEFAULT_MODULE)->set_log_size(size)
#define SET_LOG_SPACE(size)                 CLogFactory::get_instance(DEFAULT_MODULE)->set_log_space(size)

#define LOG_TRACE(format, ...)              CLogFactory::get_instance(DEFAULT_MODULE)->writeline(LOG_LEVEL_TRACE, format, ## __VA_ARGS__)
#define LOG_INFO(format, ...)               CLogFactory::get_instance(DEFAULT_MODULE)->writeline(LOG_LEVEL_INFO, format, ## __VA_ARGS__)
#define LOG_WARNING(format, ...)            CLogFactory::get_instance(DEFAULT_MODULE)->writeline(LOG_LEVEL_WARNING, format, ## __VA_ARGS__)
#define LOG_ERROR(format, ...)              CLogFactory::get_instance(DEFAULT_MODULE)->writeline(LOG_LEVEL_ERROR, format, ## __VA_ARGS__)

#else

//多实例API
#define SET_LOG_NAME(module, filepath)      CLogFactory::get_instance(module)->set_log_filepath(filepath)
#define SET_LOG_LEVEL(module, level)        CLogFactory::get_instance(module)->set_log_level(level)
#define SET_LOG_SIZE(module, size)          CLogFactory::get_instance(module)->set_log_size(size)
#define SET_LOG_SPACE(module, size)         CLogFactory::get_instance(module)->set_log_space(size)

#define LOG_TRACE(module, format, ...)      CLogFactory::get_instance(module)->writeline(LOG_LEVEL_TRACE, format, ## __VA_ARGS__)
#define LOG_INFO(module, format, ...)       CLogFactory::get_instance(module)->writeline(LOG_LEVEL_INFO, format, ## __VA_ARGS__)
#define LOG_WARNING(module, format, ...)    CLogFactory::get_instance(module)->writeline(LOG_LEVEL_WARNING, format, ## __VA_ARGS__)
#define LOG_ERROR(module, format, ...)      CLogFactory::get_instance(module)->writeline(LOG_LEVEL_ERROR, format, ## __VA_ARGS__)

#endif

//日志级别
enum _log_level
{
    LOG_LEVEL_ERROR     = 1,  //错误
    LOG_LEVEL_WARNING   = 2,  //警告
    LOG_LEVEL_INFO      = 3,  //普通
    LOG_LEVEL_TRACE     = 4,  //调试
    LOG_LEVEL_MAX
};

#ifndef __MY_LOCK__
#define __MY_LOCK__

#ifdef WIN32
#include <Windows.h>
#else
#include <pthread.h>
#endif

class MutexLock
{
#ifdef WIN32
private:
    CRITICAL_SECTION m_lock;
public:
    MutexLock(void) {InitializeCriticalSection(&m_lock);}
    virtual ~MutexLock(void) {DeleteCriticalSection(&m_lock);}
    void lock() {EnterCriticalSection(&m_lock);}
    void unlock() {LeaveCriticalSection(&m_lock);}
#else
private:
    pthread_mutex_t m_lock;
public:
    MutexLock(void) {pthread_mutex_init(&m_lock, NULL);}
    virtual ~MutexLock(void) {pthread_mutex_destroy(&m_lock);}
    void lock() {pthread_mutex_lock(&m_lock);}
    void unlock() {pthread_mutex_unlock(&m_lock);}
#endif
};
#endif //__MY_LOCK__

typedef unsigned int  uint;
typedef unsigned long uint32;

#ifdef _WIN32
typedef unsigned __int64 uint64;
#else
typedef unsigned long long uint64;
#endif

#define MAX_TIME_STR_LEN    30

typedef struct
{
    string file_path;   //文件路径
    uint64 size;        //文件大小
    time_t mtime;       //修改时间
}file_info;

typedef vector<file_info>   file_list;

class CLog
{
public:
    CLog(void);
    ~CLog(void);

    //设置日志文件路径
    void set_log_filepath(const string filepath) {m_log_filename = filepath; mk_dir(); rotate_log();}

    //设置日志文件大小切换, 单位byte
    void set_log_size(uint size) {m_log_size = size;}

    //设置日志文件占用磁盘空间大小, 单位byte
    void set_log_space(uint64 size) {m_max_log_space = size;}

    //设置日志级别
    void set_log_level(uint level) {m_log_level = (level > LOG_LEVEL_MAX) ? LOG_LEVEL_MAX : level;}

    //设置日志清理状态
    void set_clean_status(bool status) {m_lock.lock(); m_is_cleaning = status; m_lock.unlock();}

    string& get_log_path() {return m_log_filename;}
    uint64 get_max_space() {return m_max_log_space;}

    //写入一行日志
    int writeline(uint level, const char* format_str, ...);

private:
    void    rotate_log();                       //日志切换
    bool    mk_dir();                           //检查目录是否存在,不存在的话循环创建
    char*   get_time_str(bool is_write=true);   //获取当前时间字符串
    bool    rename_file();                      //取当前时间重命名日志文件
    int     get_thread_id();                    //获取当前进程id
    void    clean_logs();                       //清理日志文件
	unsigned long get_file_size(const char* filename); //获取文件大小
    //日志文件清理线程
#ifdef WIN32
    static void clean_logs_thread_fun(void* param);
#else
    static void* clean_logs_thread_fun(void* param);
#endif

    //根据日志文件名获取相关日志列表
    static bool get_log_files(const string& log_path, file_list& files);
    //根据日志文件名获取日志目录(末尾带有'\'或'/')
    static string get_log_dir(const string& log_path);

private:
    MutexLock   m_lock;                         //同步锁,用于多线程同步写
    string      m_log_filename;                 //日志文件路径名
    FILE*       m_fp;                           //日志文件句柄
    uint        m_log_level;                    //设置的日志级别
    uint        m_log_size;                     //设置的日志文件大小
    uint64      m_max_log_space;                //设置日志文件占用磁盘空间大小
    bool        m_is_cleaning;                  //是否正在进行日志清理

    char        m_time_str[MAX_TIME_STR_LEN];   //时间字符串buf
};

#define MAX_LOG_INSTANCE    10
#define MAX_MODULE_LEN      30

typedef struct _log_instance
{
    char  name[MAX_MODULE_LEN];
    CLog* plog;
}log_inst;

class CLogFactory
{
public:
    CLogFactory(void);
    virtual ~CLogFactory(void);

    static CLog* get_instance(const char* name);
    static void  free_instance(const char* name);

private:
    static void  free_all_inst();

private:
    static log_inst     m_inst_list[MAX_LOG_INSTANCE];      //log实例列表
    static uint         m_inst_num;                         //log实例数量
    static MutexLock    m_lock;                             //同步锁
};

#endif // __Log_h__

