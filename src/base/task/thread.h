#ifndef __THREAD_H__
#define __THREAD_H__

#include <unistd.h>
#include <sys/types.h>
#include "types.h"

class Thread
{
public:
    Thread() : m_tid(-1), m_bStop(false) {}
    virtual ~Thread();

    SInt32 Start();
    void   Stop() { m_bStop = true; }
    bool   IsStop() { return m_bStop; }

    static void* ThreadEntry(void* i_pArg);

    virtual void Entry() = 0;

    SInt32 ThreadYield();
protected:
    pthread_t m_tid;
    bool m_bStop;
};

#endif
