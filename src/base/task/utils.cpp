#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <assert.h>
#include <errno.h>
#include <stdarg.h>  // For va_start, etc.
#include "utils.h"

#define MAX_REGEX_MATCH_NUM     (50)
#define MAX_FORMAT_STR_LEN      (1024)

void SleepUs(UInt64 us)
{
    struct timeval tval;
    tval.tv_sec = us / US_IN_1SEC;
    tval.tv_usec = us % US_IN_1SEC;
    select(0, NULL, NULL, NULL, &tval);
}

void SleepMs(UInt64 ms)
{
    SleepUs(ms * US_IN_1MS);
}

UInt64 Nanoseconds()
{
    struct timespec ts = {0};
    SInt32 s32Ret = ::clock_gettime(CLOCK_MONOTONIC, &ts); // Need link with -lrt.
    assert(s32Ret == 0);
    return (UInt64)ts.tv_sec * NS_IN_1SEC + ts.tv_nsec;
}

UInt64 MicroSeconds()
{
    return Nanoseconds() / NS_IN_1US; // ms -> us
}

UInt64 MilliSeconds()
{
    return MicroSeconds() / US_IN_1MS; // us -> ms
}

bool RegexMatch(const string &i_strRegx, const string &i_strSrc, SInt32 i_s32Flags, StringVector &o_vecMatchs)
{
    o_vecMatchs.clear();

    regex_t reg;
    char errbuf[1024] = {0};
    int err = regcomp(&reg, i_strRegx.c_str(), i_s32Flags);
    if (err < 0)
    {
        regerror(err, &reg, errbuf, sizeof(errbuf));
        printf("###### Compile regex string <%s> failed! error<%d-%s>\n", i_strRegx.c_str(), err, errbuf);
        return false;
    }

    regmatch_t atMatchs[MAX_REGEX_MATCH_NUM+1] = {{0}};
    err = regexec(&reg, i_strSrc.c_str(), MAX_REGEX_MATCH_NUM, atMatchs, 0);
    if (REG_NOMATCH == err)
    {
        // printf("No match record! i_strRegx<%s>, i_strSrc<%s>\n", i_strRegx.c_str(), i_strSrc.c_str());
        regfree(&reg);
        return false;
    }
    else if (err)
    {
        // regerror(err, &reg, errbuf, sizeof(errbuf));
        // printf("Regex match failed! i_strRegx<%s>, i_strSrc<%s>, error<%d-%s>\n",
        //     i_strRegx.c_str(), i_strSrc.c_str(), err, errbuf);
        regfree(&reg);
        return false;
    }
    // 跳过完整匹配项，即tMatchs[0]
    for (UInt32 i = 1; i < MAX_REGEX_MATCH_NUM && atMatchs[i].rm_so != -1; i++)
    {
        UInt32 u32Len = atMatchs[i].rm_eo - atMatchs[i].rm_so;
        if (u32Len > 0)
        {
            string strMatch = i_strSrc.substr(atMatchs[i].rm_so, u32Len);
            o_vecMatchs.push_back(strMatch);
        }
    }
    regfree(&reg);
    return true;
}

bool StartsWith(const string &i_strFull, const string &i_strStarting)
{
    if (i_strStarting.size() > i_strFull.size()) return false;
    return std::equal(i_strStarting.begin(), i_strStarting.end(), i_strFull.begin());
}

bool EndsWith(const string &i_strFull, const string &i_strEnding)
{
    if (i_strEnding.size() > i_strFull.size()) return false;
    return std::equal(i_strEnding.rbegin(), i_strEnding.rend(), i_strFull.rbegin());
}


string StringFormat(const char *fmt, ...)
{
    char acBuf[MAX_FORMAT_STR_LEN] = {0};

    va_list ap;
    va_start(ap, fmt);
    vsnprintf(acBuf, sizeof(acBuf), fmt, ap);
    va_end(ap);

    return acBuf;
}

bool InStr(const string &i_strSub, const string &i_strFull)
{
    return i_strFull.find(i_strSub) != string::npos;
}

StringVector &SplitString(const string &i_strOrigin, const string &i_strSeps,
                        StringVector &o_vecElems, UInt32 i_u32MaxSplitNum)
{
    o_vecElems.clear();

    string::size_type pos1, pos2;
    pos1 = 0;
    pos2 = i_strOrigin.find(i_strSeps);
    UInt32 i = 0;
    while (string::npos != pos2)
    {
        string strSub = i_strOrigin.substr(pos1, pos2-pos1);
        o_vecElems.push_back(trim(strSub));

        pos1 = pos2 + i_strSeps.size();
        if (i_u32MaxSplitNum > 0 && (++i) >= i_u32MaxSplitNum)
        {
            break;
        }
        pos2 = i_strOrigin.find(i_strSeps, pos1);
    }
    if (pos1 != i_strOrigin.length())
    {
        string strSub = i_strOrigin.substr(pos1, pos2-pos1);
        o_vecElems.push_back(trim(strSub));
    }
    return o_vecElems;
}

string& ltrim(string &io_strOrigin, const string &i_strTrimChars)
{
    string::size_type pos = io_strOrigin.find_first_not_of(i_strTrimChars);
    if (pos != string::npos)
    {
        io_strOrigin.erase(0, pos);
    }
    return io_strOrigin;
}

string& rtrim(string &io_strOrigin, const string &i_strTrimChars)
{
    string::size_type pos = io_strOrigin.find_last_not_of(i_strTrimChars);
    if (pos != string::npos)
    {
        io_strOrigin.erase(pos+1);
    }
    return io_strOrigin;
}

string& trim(string &io_strOrigin, const string &i_strTrimChars)
{
    return ltrim(rtrim(io_strOrigin));
}

string ToLower(string &io_strData)
{
    std::transform(io_strData.begin(), io_strData.end(), io_strData.begin(), ::tolower);
    return io_strData;
}

string ToUpper(string &io_strData)
{
    std::transform(io_strData.begin(), io_strData.end(), io_strData.begin(), ::toupper);
    return io_strData;
}

UInt32 GetCpuNum()
{
    return sysconf(_SC_NPROCESSORS_ONLN);
}

bool FileExist(const string &i_strFile)
{
    struct stat tStat = {0};
    return (0 == stat(i_strFile.c_str(), &tStat));
}

SInt32 SetMaxFdNum(UInt32 i_u32MaxNum)
{
    struct rlimit rl;
    rl.rlim_cur = i_u32MaxNum;
    rl.rlim_max = i_u32MaxNum;
    SInt32 s32Ret = setrlimit(RLIMIT_NOFILE, &rl);
    if (s32Ret != 0)
    {
        printf("###### setrlimit() failed with errno %d\n", errno);
    }
    return s32Ret;
}

