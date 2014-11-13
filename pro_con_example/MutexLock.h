#ifndef MUTEXLOCK_H
#define MUTEXLOCK_H

#include "NonCopyable.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//用于pthread系列函数的返回值检查
#define TINY_CHECK(exp) \
    if(!(exp)) \
    {   \
        fprintf(stderr, "File:%s, Line:%d Exp:[" #exp "] is true, abort.\n", __FILE__, __LINE__); abort();\
    }
	
class MutexLock : NonCopyable
{
public:
	MutexLock();
	~MutexLock();
	void lock();
	void unlock();
	
	bool isLocking() const { return isLocking_; }
	pthread_mutex_t *getMutexPtr()
	{
		return &mutex_;
	}
private:
	pthread_mutex_t mutex_;
	bool isLocking_;
};

class MutexLockGuard : NonCopyable
{
public:
	MutexLockGuard(MutexLock &mutex)
		:mutex_(mutex)
	{
		mutex_.lock();
	}
	~MutexLockGuard()
	{
		mutex_.unlock();
	}
private:
	MutexLock &mutex_;
};

#endif //MUTEXLOCK_H

