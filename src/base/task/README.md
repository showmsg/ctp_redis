## Task

简单的Task调度框架，仿照Darwin Streaming Server中的Task机制实现


## Demo

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
        TaskThreadPool::AddThreads(2);
    
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
    
    
### Result
    
    [root@zmsstest Task]# ./demo_task 
    PrintTask: kStartEvent
    PrintTask: kIdleEvent, 14926901778 ms
    PrintTask: kIdleEvent, 14926902779 ms
    PrintTask: kIdleEvent, 14926903780 ms
    PrintTask: kIdleEvent, 14926904780 ms
    PrintTask: kIdleEvent, 14926905781 ms
    main: send kill event
    PrintTask: kIdleEvent, 14926906781 ms
    PrintTask: kKillEvent, kill myself
