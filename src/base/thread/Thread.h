#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>

//抽象类
class Thread
{
public:
	Thread();
	virtual ~Thread();//虚析构函数

	void Start();//线程的启动方法
	void Join();//等待线程结束并且收回被等待线程的资源

	void SetAutoDelete(bool autoDelete);

private:
	static void* ThreadRoutine(void* arg);//线程入口函数  也是静态全局函数
	virtual void Run() = 0;  
	//纯虚函数 //线程执行体run,通过继承类实现不同的线程函数run
	pthread_t threadId_;//线程ID
	bool autoDelete_;
};

#endif // _THREAD_H_
