#ifndef CONSUMER_H_
#define CONSUMER_H_

#include "Thread.h"

class Buffer;

class ConsumerThread : public Thread
{
public:
	ConsumerThread(Buffer &buffer);
	void run();
private:
	Buffer &buffer_;
};

#endif //CONSUMER_H_