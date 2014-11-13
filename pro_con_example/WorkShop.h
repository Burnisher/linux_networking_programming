#ifndef WORKSHOP_H_
#define WORKSHOP_H_

#include "NonCopyable.h"
#include "Buffer.h"
#include <vector>

class ProducerThread;
class ConsumerThread;

class WorkShop : NonCopyable
{
public:
	WorkShop(size_t buffersize,
			 size_t producerSize,
			 size_t consumerSize);
	~WorkShop();

	void startWorking();
private:
	size_t bufferSize_;
	Buffer buffer_;
	
	size_t producerSize_;
	size_t consumerSize_;
	std::vector<ProducerThread*> producers_;
	std::vector<ConsumerThread*> consumers_;
};

#endif //WORKSHOP_H_