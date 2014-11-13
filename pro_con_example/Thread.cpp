#include "Thread.h"
#include <iostream> //debug
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */
using namespace std;

Thread::Thread()
	:threadId_(0),
	 isRunning_(false)
{

}

Thread::~Thread()//确保回收进程
{
	if(isRunning_
	)
	{
		pthread_detach(threadId_);
	}
}

void Thread::start()
{
	if(pthread_create(&threadId_, NULL, runInThread, this) != 0)
	{
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	isRunning_ = true;
}

void Thread::join()
{
	assert(isRunning_);
	pthread_join(threadId_, NULL);
	isRunning_ = false;
}

 void *Thread::runInThread(void *arg)
 {
	Thread *pt = static_cast<Thread *>(arg);
	pt->run();
	pthread_exit(NULL);
	return NULL;
 }

