#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include "thread.h"

Thread::~Thread()
{
    void* pRetVal = NULL;
    SInt32 s32Ret = pthread_join(m_tid, &pRetVal);
    if (0 != s32Ret)
    {
        printf("pthread_join error! errno %d\n", errno);
    }
}

SInt32 Thread::Start()
{
    SInt32 s32Ret = pthread_create(&m_tid, NULL, Thread::ThreadEntry, this);
    if (0 != s32Ret)
    {
        printf("pthread_create error! errno %d-%s\n", errno, strerror(errno));
    }
    return s32Ret;
}

void* Thread::ThreadEntry(void* i_pArg)
{
    Thread *pThread = (Thread*)i_pArg;
    pThread->Entry();
    return NULL;
}

SInt32 Thread::ThreadYield()
{
    return pthread_yield();
}
