#include "Thread.h"
#include <iostream>
using namespace std;


Thread::Thread() : autoDelete_(false)//构造函数
{
//	cout<<"Thread ..."<<endl;
}

Thread::~Thread() //析构函数
{
//	cout<<"~Thread ..."<<endl;
}

void Thread::Start()//启动线程
{
	pthread_create(&threadId_, NULL, ThreadRoutine, this);
	//第三个参数这里并不能直接放上执行函数run
	//因为run函数式普通的成员函数，隐含的第一个参数是Thread*(就是this)
	//调用的时候是thiscall约定，也就是说他不能做为入口函数
}

void Thread::Join() //等待线程执行结束并且收回被等待线程的资源
{
	pthread_join(threadId_, NULL);
}

void* Thread::ThreadRoutine(void* arg)//
{
	Thread* thread = static_cast<Thread*>(arg);//派生类指针转换成基类指针
	thread->Run();
	if (thread->autoDelete_)
		delete thread;
	return NULL;
}

void Thread::SetAutoDelete(bool autoDelete)
{
	autoDelete_ = autoDelete;
}
