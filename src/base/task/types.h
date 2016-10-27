#ifndef __TYPES_H__
#define __TYPES_H__

#include <unistd.h>
#include <sys/types.h>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

#ifdef DEBUG
    #include <time.h>
    #include <stdio.h>
    #define TRACE(fmt, ...)     printf("[Time:%d]" fmt " -- [%s:%d]\n", (int)time(NULL), ## __VA_ARGS__, __FILE__, __LINE__)
#else
    #define TRACE(fmt, ...)
#endif

typedef signed char             SInt8;
typedef unsigned char           UInt8;
typedef signed short            SInt16;
typedef unsigned short          UInt16;
typedef signed int              SInt32;
typedef unsigned int            UInt32;
typedef signed long long        SInt64;
typedef unsigned long long      UInt64;

typedef vector<UInt32>          UInt32Vector;
typedef vector<string>          StringVector;
typedef map<string, string>     StringMap;

#endif
