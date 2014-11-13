#ifndef PRODUCER_H_
#define PRODUCER_H_

#include "Thread.h"

class Buffer;

class ProducerThread : public Thread
{
public:
	ProducerThread(Buffer &buffer);
	void run();

private:
	Buffer &buffer_;
};

#endif //PRODUCER_H_