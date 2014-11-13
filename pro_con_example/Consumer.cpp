#include "Consumer.h"
#include "Buffer.h"
#include <stdio.h>
#include <unistd.h>


ConsumerThread::ConsumerThread(Buffer &buffer)
	:buffer_(buffer)
{
	
}

void ConsumerThread::run()
{	
	while(1)
	{
		int num = buffer_.pop();
		 printf("pop a num %d, size = %u\n", num, buffer_.size());
		
		::sleep(3);
	}
}




