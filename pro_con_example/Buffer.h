#ifndef BUFFER_H_
#define BUFFER_H_

#include "NonCopyable.h"
#include "MutexLock.h"
#include "Condition.h"
#include <queue>

class Buffer : NonCopyable
{
public:
	Buffer(size_t size);
	void push(int val);
	int pop();
	
	bool empty() const;
	size_t size() const;
	
private:
	mutable MutexLock mutex_;
	Condition full_;
	Condition empty_;
	
	size_t size_;
	std::queue<int> queue_;
};

#endif //BUFFER_H_
