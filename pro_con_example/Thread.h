#ifndef THREAD_H_
#define THREAD_H_

#include "NonCopyable.h"
#include <pthread.h>
#include <sys/types.h>

class Thread : NonCopyable
{
public:
	Thread();
	~Thread();
	
	void start();
	void join();
	
	virtual void run() = 0;
	
	pthread_t getThreadId() const
	{ return threadId_; }
private:
	static void *runInThread(void *arg);
	
	pthread_t threadId_;
	
	bool isRunning_;
};

#endif //THREAD_H_