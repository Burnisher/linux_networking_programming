#ifndef CONDITION_H_
#define CONDITION_H_

#include "NonCopyable.h"
#include <pthread.h>

class MutexLock;

class Condition : NonCopyable
{
public:
	Condition(MutexLock &mutex);
	~Condition();
	
	void wait();
	void notify();
	void notifyall();
private:
	pthread_cond_t cond_;
	MutexLock &mutex_;
};

#endif //CONDITION_H_