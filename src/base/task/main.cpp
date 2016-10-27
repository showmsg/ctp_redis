#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include "utils.h"

class PrintTask : public Task
{
public:
    PrintTask() : Task() {}
    void Init()
    {
        Signal(Task::kStartEvent);
    }
    SInt64 Run()
    {
        EventFlags events = GetEvents();
        if (events & kStartEvent)
        {
            printf("PrintTask: kStartEvent\n");
        }
        if (events & kTimeoutEvent)
        {
            printf("PrintTask: kTimeoutEvent\n");
        }
        if (events & kIdleEvent)
        {
            printf("PrintTask: kIdleEvent, %llu ms\n", MilliSeconds());
        }

        if (events & kKillEvent)
        {
            printf("PrintTask: kKillEvent, kill myself\n");
            return -1;
        }

        return 1*1000;
    }
};

int main(int argc, char *argv[])
{
    TaskThreadPool::AddThreads(1);

    PrintTask *pTask = new PrintTask();
    pTask->Init();

    SleepUs(5*1000*1000);// sleep 5s

    printf("main: send kill event\n");
    pTask->Signal(Task::kKillEvent);
    pTask = NULL;

    SleepUs(1*1000*1000);// sleep 1s
    TaskThreadPool::RemoveThreads();

    return 0;
}
