#include "Buffer.h"

Buffer::Buffer(size_t size)
	:full_(mutex_),
	 empty_(mutex_),
	 size_(size)
{

}

void Buffer::push(int val)
{
	{
		MutexLockGuard lock(mutex_);
		while(queue_.size() >= size_)
		{
			empty_.wait();
		}
		queue_.push(val);
	}
	full_.notify();
}

int Buffer::pop()
{
	int temp = 0;
	{
		MutexLockGuard lock(mutex_);
		while(queue_.empty())
		{
			full_.wait();
		}
		temp = queue_.front();
		queue_.pop();
	}
	empty_.notify();
	
	return temp;
}

bool Buffer::empty() const
{
	MutexLockGuard lock(mutex_);
	return queue_.empty();
}

size_t Buffer::size() const
{
	MutexLockGuard lock(mutex_);
	return queue_.size();
}

