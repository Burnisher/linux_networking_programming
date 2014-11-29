#include "Condition.h"
#include "MutexLock.h"
#include <assert.h>

namespace Tiny
{

Condition::Condition(MutexLock &mutex)
	:mutex_(mutex)
{
	TINY_CHECK(!pthread_cond_init(&cond_, NULL));
}

Condition::~Condition()
{
	TINY_CHECK(!pthread_cond_destroy(&cond_));
}

void Condition::wait()
{
	assert(mutex_.isLocking());
	TINY_CHECK(!pthread_cond_wait(&cond_, mutex_.getMutexPtr()));
    mutex_.restoreMutexStatus();
}

void Condition::notify()
{
	TINY_CHECK(!pthread_cond_signal(&cond_));
}

void Condition::notifyAll()
{
	TINY_CHECK(!pthread_cond_broadcast(&cond_));
}

}
