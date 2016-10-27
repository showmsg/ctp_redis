/* 
 * Thread.h 
 * 
 *  Created on: 2008-10-13 
 *      Author: root 
 */  
#ifndef THREAD_H_  
#define THREAD_H_  
#include <unistd.h>  
#include <pthread.h>  
class Runnable  
{  
    public:  
        //运行实体  
        virtual void run() = 0;  
};  
//线程类  
class Thread: public Runnable  
{  
    private:  
        //线程初始化号  
        static int thread_init_number;  
        //当前线程初始化序号  
        int current_thread_init_number;  
        //线程体  
        Runnable *target;  
        //当前线程的线程ID  
        pthread_t tid;  
        //线程的状态  
        int thread_status;  
        //线程属性  
        pthread_attr_t attr;  
        //线程优先级  
        sched_param param;  
        //获取执行方法的指针  
        static void* run0(void* pVoid);  
        //内部执行方法  
        void* run1();  
        //获取线程序号  
        static int get_next_thread_num();  
    public:  
        //线程的状态－新建  
        static const int THREAD_STATUS_NEW = 0;  
        //线程的状态－正在运行  
        static const int THREAD_STATUS_RUNNING = 1;  
        //线程的状态－运行结束  
        static const int THREAD_STATUS_EXIT = -1;  
        //构造函数  
        Thread();  
        //构造函数  
        Thread(Runnable *target);  
        //析构  
        ~Thread();  
        //线程的运行体  
        void run();  
        //开始执行线程  
        bool start();  
        //获取线程状态  
        int get_state();  
        //等待线程直至退出  
        void join();  
        //等待线程退出或者超时  
        void join(unsigned long millis_time);  
        //比较两个线程时候相同，通过current_thread_init_number判断  
        bool operator ==(const Thread* other_pthread);  
        //获取this线程ID  
        pthread_t get_thread_id();  
        //获取当前线程ID  
        static pthread_t get_current_thread_id();  
        //当前线程是否和某个线程相等，通过tid判断  
        static bool is_equals(Thread* iTarget);  
        //设置线程的类型:绑定/非绑定  
        void set_thread_scope(bool isSystem);  
        //获取线程的类型:绑定/非绑定  
        bool get_thread_scope();  
        //设置线程的优先级，1－99，其中99为实时，意外的为普通  
        void set_thread_priority(int priority);  
        //获取线程的优先级  
        int get_thread_priority();  
};  
int Thread::thread_init_number = 1;  
inline int Thread::get_next_thread_num()  
{  
    return thread_init_number++;  
}  
void* Thread::run0(void* pVoid)  
{  
    Thread* p = (Thread*) pVoid;  
    p->run1();  
    return p;  
}  
void* Thread::run1()  
{  
    thread_status = THREAD_STATUS_RUNNING;  
    tid = pthread_self();  
    run();  
    thread_status = THREAD_STATUS_EXIT;  
    tid = 0;  
    pthread_exit(NULL);  
}  
void Thread::run()  
{  
    if (target != NULL)  
    {  
        (*target).run();  
    }  
}  
Thread::Thread()  
{  
    tid = 0;  
    thread_status = THREAD_STATUS_NEW;  
    current_thread_init_number = get_next_thread_num();  
    pthread_attr_init(&attr);  
}  
Thread::Thread(Runnable *iTarget)  
{  
    target = iTarget;  
    tid = 0;  
    thread_status = THREAD_STATUS_NEW;  
    current_thread_init_number = get_next_thread_num();  
    pthread_attr_init(&attr);  
}  
Thread::~Thread()  
{  
    pthread_attr_destroy(&attr);  
}  
bool Thread::start()  
{  
    return pthread_create(&tid, &attr, run0, this);  
}  
inline pthread_t Thread::get_current_thread_id()  
{  
    return pthread_self();  
}  
inline pthread_t Thread::get_thread_id()  
{  
    return tid;  
}  
inline int Thread::get_state()  
{  
    return thread_status;  
}  
void Thread::join()  
{  
    if (tid > 0)  
    {  
        pthread_join(tid,NULL);  
    }  
}  
void Thread::join(unsigned long millis_time)  
{  
    if (tid == 0)  
    {  
        return;  
    }  
    if (millis_time == 0)  
    {  
        join();  
    }  
    else  
    {  
        unsigned long k = 0;  
        while (thread_status != THREAD_STATUS_EXIT && k <= millis_time)  
        {  
            usleep(100);  
            k++;  
        }  
    }  
}  
bool Thread::operator ==(const Thread* other_pthread)  
{  
    if(other_pthread==NULL)  
    {  
        return false;  
    }if(current_thread_init_number==(*other_pthread).current_thread_init_number)  
    {  
        return true;  
    }  
    return false;  
}  
bool Thread::is_equals(Thread* iTarget)  
{  
    if (iTarget == NULL)  
    {  
        return false;  
    }  
    return pthread_self() == iTarget->tid;  
}  
void Thread::set_thread_scope(bool isSystem)  
{  
    if (isSystem)  
    {  
        pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);  
    }  
    else  
    {  
        pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);  
    }  
}  
void Thread::set_thread_priority(int priority)  
{  
    pthread_attr_getschedparam(&attr,&param);  
    param.__sched_priority = priority;  
    pthread_attr_setschedparam(&attr,&param);  
}  
int Thread::get_thread_priority(){  
    pthread_attr_getschedparam(&attr,&param);  
    return param.__sched_priority;  
}  
#endif /* THREAD_H_ */  

以为newmain.cpp代码  
/* 
 * newmain.cpp 
 * 
 *  Created on: 2008-10-13 
 *      Author: root 
 */  
#include "Thread.h"  
#include <iostream>  
class MutilThread: public Thread  
{  
    public:  
        Thread* th1;  
        Thread* th2;  
        void Test()  
        {  
            th1 = new Thread(this);  
            th1->set_thread_priority(90);  
            th2 = new Thread(this);  
            start();  
            th1->start();  
            th2->start();  
            th1->join();  
            th2->join();  
        }  
        void run()  
        {  
            if (Thread::is_equals(th1))  
            {  
                int number = 100;  
                for (int i = 0; i < 10; i++)  
                {  
                    std::cout << "this thread1 number is: " << number++  
                        << std::endl;  
                    std::cout << "\t pid is: " << getpid() << " tid is "  
                        << get_current_thread_id() << std::endl;  
                    sleep(1);  
                }  
            }  
            else if (Thread::is_equals(th2))  
            {  
                int number = 200;  
                for (int i = 0; i < 10; i++)  
                {  
                    std::cout << "this is thread2 number is: " << number++  
                        << std::endl;  
                    std::cout << "\t pid is: " << getpid() << " tid is "  
                        << get_current_thread_id() << std::endl;  
                    sleep(1);  
                }  
            }  
            else if (Thread::is_equals(this))  
            {  
                int number = 300;  
                for (int i = 0; i < 10; i++)  
                {  
                    std::cout << "this is thread0 number is: " << number++  
                        << std::endl;  
                    std::cout << "\t pid is: " << getpid() << " tid is "  
                        << get_current_thread_id() << std::endl;  
                    sleep(1);  
                }  
            }  
        }  
};  
int main(int argc, char **argv) {  
    bool ret;  
    MutilThread *mt;  
    mt = new MutilThread();  
    mt->Test();  
    return (EXIT_SUCCESS);  
} 
