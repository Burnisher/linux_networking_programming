#include "Producer.h"
#include "Buffer.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


ProducerThread::ProducerThread(Buffer &buffer)
	:buffer_(buffer)
{
	::srand(12345);
}

void ProducerThread::run()
{
	while(1)
	{
		int num = rand()%100;
		buffer_.push(num);
		printf("push a num %d, size = %u\n", num, buffer_.size());
		
		::sleep(2);
	}
	
}