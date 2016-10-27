#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <pthread.h>
#include <assert.h>
#include "utils.h"

typedef pthread_mutex_t     mutex_t;
typedef pthread_condattr_t  condattr_t;
typedef pthread_cond_t      cond_t;

class Mutex
{
public:
    Mutex(void)             { pthread_mutex_init(&m_lock, NULL); }
    virtual ~Mutex(void)    { pthread_mutex_destroy(&m_lock); }
    inline void Lock()      { pthread_mutex_lock(&m_lock); }
    inline void Unlock()    { pthread_mutex_unlock(&m_lock); }
    mutex_t& GetMutex()     { return m_lock; }
private:
    mutex_t m_lock;
};


class AutoMutex
{
public:
    AutoMutex(Mutex *i_pMutex) : m_pMutex(i_pMutex) { m_pMutex->Lock(); }
    virtual ~AutoMutex(void) { m_pMutex->Unlock(); }
private:
    Mutex *m_pMutex;
};

class Cond
{
public:
    Cond()
    {
        condattr_t attr;
        pthread_condattr_init(&attr);
        pthread_condattr_setclock(&attr, CLOCK_MONOTONIC);
        pthread_cond_init(&m_cond, &attr);
    }
    ~Cond() {}

    inline void Signal()
    {
        assert(0 == pthread_cond_signal(&m_cond));
    }
    inline UInt32 Wait(Mutex &i_Mutex, SInt32 i_s32TimeoutMs = 0)
    {
        SInt32 s32Ret = 0;
        if (i_s32TimeoutMs > 0)
        {
            UInt64 u64CurTime = Nanoseconds();
            UInt64 u64ns = u64CurTime + (UInt64)i_s32TimeoutMs * NS_IN_1MS;
            struct timespec ts;
            ts.tv_sec = u64ns / NS_IN_1SEC;
            ts.tv_nsec = u64ns % NS_IN_1SEC;
            s32Ret = pthread_cond_timedwait(&m_cond, &i_Mutex.GetMutex(), &ts);
        }
        else
        {
            s32Ret = pthread_cond_wait(&m_cond, &i_Mutex.GetMutex());
        }
        return s32Ret;
    }
    inline void Broadcast()
    {
        assert(0 == pthread_cond_broadcast(&m_cond));
    }
private:
    cond_t m_cond;
};

#endif
