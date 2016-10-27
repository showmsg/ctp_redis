#include <stdio.h>
#include "task.h"
#include "utils.h"

#define MIN_WAIT_TIME_MS        10
#define MAX_RUN_TIMES_ONCE      10

UInt32 TaskThreadPool::m_u32ThreadNum = 0;
UInt32 TaskThreadPool::m_u32ThreadPicker = 0;
ThreadVector TaskThreadPool::m_vecThreads;
bool TaskThreadPool::m_bRunning = false;

void Task::Signal(Task::EventFlags i_Events, SInt64 i_Priority)
{
    if (!this->IsValid()) return;

    EventFlags oldEvents = m_Events;
    i_Events |= kAlive;
    m_Events |= i_Events;
    // TRACE("0.Signal: Task %p, i_Events %d, i_Priority %lld, IsAlive %d, ThreadNum %d",
    //       this, i_Events, i_Priority, oldEvents & kAlive ? 1 : 0, TaskThreadPool::GetThreadNum());
    if ((i_Priority > 0 || !(oldEvents & kAlive)) && TaskThreadPool::GetThreadNum() > 0)
    {
        // TRACE("1.Signal: Task %p, i_Events %d, i_Priority %lld", this, i_Events, i_Priority);
        TaskThreadPool::AddTask(this, i_Priority);
        // TRACE("2.Signal: Task %p, i_Events %d, i_Priority %lld", this, i_Events, i_Priority);
    }
}

Task::EventFlags Task::GetEvents()
{
    Task::EventFlags events = m_Events & kAliveOff;
    m_Events -= events;
    return events;
}

TaskThread::~TaskThread()
{
    Stop();
    AutoMutex mutex(&m_lock);
    while (!m_TaskQueue.empty())
    {
        m_TaskQueue.pop();
    }
}

void TaskThread::Entry()
{
    while (!IsStop())
    {
        Task *pTask = WaitForTask();
        if (NULL == pTask || !pTask->IsValid()) return;

        TRACE("GetTask %p", pTask);
        SInt32 s32MaxRunTimes = MAX_RUN_TIMES_ONCE;
        while (s32MaxRunTimes-- > 0)
        {
            SInt64 ret = pTask->Run();
            if (ret > 0)
            {
                s32MaxRunTimes = 0;
                pTask->Signal(Task::kIdleEvent, ret);
            }
            else if (0 == ret)
            {
                if (pTask->ClearEventsWhenOnlyAlive())
                {
                    s32MaxRunTimes = 0;
                }
                else
                {
                    pTask->Signal(Task::kIdleEvent);
                }
            }
            else if (ret < 0)
            {
                s32MaxRunTimes = 0;
                delete pTask;
                pTask = NULL;
            }
            ThreadYield();
        }
    }
}

void TaskThread::AddTask(Task* i_pTask, SInt64 i_Priority)
{
    i_Priority = i_Priority*US_IN_1MS + MicroSeconds();
    T_Node n(i_Priority, i_pTask);
    AutoMutex mutex(&m_lock);
    m_TaskQueue.push(n);
    TRACE("AddTask: pTask %p, Time %lld", i_pTask, i_Priority);
}

Task* TaskThread::WaitForTask()
{
    while (!IsStop())
    {
        if (m_TaskQueue.empty())
        {
            SleepUs(1000); // sleep 1ms
            ThreadYield();
        }
        else
        {
            AutoMutex mutex(&m_lock);
            const T_Node &n = m_TaskQueue.top();
            Task* pTask = (Task*)n.pValue;
            UInt64 t = MicroSeconds();
            if (n.u64Priority > t)
            {
                SleepUs(n.u64Priority - t);
            }
            m_TaskQueue.pop();
            return pTask;
        }
    }

    return NULL;
}

void TaskThreadPool::AddThreads(UInt32 i_u32Num)
{
    if (m_vecThreads.empty())
    {
        m_u32ThreadNum = i_u32Num;
        for (UInt32 i = 0; i < i_u32Num; i ++)
        {
            TaskThread *pThread = new TaskThread();
            m_vecThreads.push_back(pThread);
            pThread->Start();
        }
        m_bRunning = true;
    }
}

void TaskThreadPool::RemoveThreads()
{
    m_bRunning = false;
    // 先停止线程
    ThreadVector::iterator it = m_vecThreads.begin();
    for (; it != m_vecThreads.end(); it++)
    {
        TaskThread *pThread = *it;
        pThread->Stop();
    }
    // 再析构线程
    it = m_vecThreads.begin();
    for (; it != m_vecThreads.end(); it++)
    {
        TaskThread *pThread = *it;
        delete pThread;
        pThread = NULL;
    }
    m_u32ThreadNum = 0;
    m_u32ThreadPicker = 0;
    m_vecThreads.clear();
}

void TaskThreadPool::AddTask(Task* i_pTask, SInt64 i_Priority)
{
    if (!m_bRunning) return;

    UInt32 u32Idx = (++m_u32ThreadPicker) % m_u32ThreadNum;
    TaskThread *pThread = m_vecThreads[u32Idx];
    if (pThread && !pThread->IsStop())
    {
        pThread->AddTask(i_pTask, i_Priority);
    }
}


