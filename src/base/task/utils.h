#ifndef __UTILS_H__
#define __UTILS_H__

#include <regex.h>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "types.h"

#define TIME_UNIT       (1000)
#define MS_IN_1SEC      TIME_UNIT
#define US_IN_1SEC      (TIME_UNIT*TIME_UNIT)
#define NS_IN_1SEC      (TIME_UNIT*TIME_UNIT*TIME_UNIT)
#define NS_IN_1MS       US_IN_1SEC
#define NS_IN_1US       TIME_UNIT
#define US_IN_1MS       TIME_UNIT

void SleepUs(UInt64 us);
void SleepMs(UInt64 ms);

UInt64 Nanoseconds();
UInt64 MicroSeconds();
UInt64 MilliSeconds();

// i_s32Flags取值：
// REG_EXTENDED 以功能更加强大的扩展正则表达式的方式进行匹配。
// REG_ICASE 匹配字母时忽略大小写。
// REG_NOSUB 不用存储匹配后的结果。
// REG_NEWLINE 识别换行符，这样'$'就可以从行尾开始匹配，'^'就可以从行的开头开始匹配。
bool RegexMatch(const string &i_strRegx, const string &i_strSrc, SInt32 i_s32Flags, StringVector &o_vecMatchs);

bool StartsWith(const string &i_strFull, const string &i_strStarting);
bool EndsWith(const string &i_strFull, const string &i_strEnding);

string StringFormat(const char *fmt, ...);

bool InStr(const string &i_strSub, const string &i_strFull);

StringVector &SplitString(const string &i_strOrigin, const string &i_strSeps,
                        StringVector &o_vecElems, UInt32 i_u32MaxSplitNum=0);

string& ltrim(string &io_strOrigin, const string &i_strTrimChars=" \r\n");
string& rtrim(string &io_strOrigin, const string &i_strTrimChars=" \r\n");
string& trim(string &io_strOrigin, const string &i_strTrimChars=" \r\n");

string ToLower(string &io_strData);
string ToUpper(string &io_strData);

UInt32 GetCpuNum();
bool FileExist(const string &i_strFile);
SInt32 SetMaxFdNum(UInt32 i_u32MaxNum);

// 模板函数必须声明和实现必须在头文件中
template <typename T>
bool InVector(const T Value, const vector<T> &i_vecValus)
{
    return std::find(i_vecValus.begin(), i_vecValus.end(), Value) != i_vecValus.end();
}

template <typename K, typename V>
bool InMap(const K Key, const map<K, V> &i_mapValus)
{
    return i_mapValus.find(Key) != i_mapValus.end();
}

template <typename T>
string ToStr(T Value)
{
    std::ostringstream oss;
    oss << Value;
    return oss.str();
}

template <class T>
string VecToStr(const vector<T> &i_vecValues, const string &i_strSep=",")
{
    std::ostringstream oss;
    UInt32 u32Len = i_vecValues.size();
    for (UInt32 i = 0; i < u32Len-1; i++)
    {
        oss << i_vecValues[i] << i_strSep;
    }
    oss << i_vecValues[u32Len-1];
    return oss.str();
}

#endif
