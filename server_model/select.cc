#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	char buffer[128];
	int result, nread;
	
	fd_set inputs, testfds;
	struct timeval timeout;
	
	FD_ZERO(&inputs);
	FD_SET(0, &inputs);
	
	while(1)
	{
		//testfds = inputs;
		timeout.tv_sec = 3;
		timeout.tv_usec = 500000;
		
		
		//FD_SET(0, &inputs);
		
		result = select(FD_SETSIZE, &inputs, NULL, NULL, &timeout);
		
		switch(result)
		{
			case 0:
				printf("timeout\n");
				break;
			case -1:
				perror("select");
				exit(1);
			default:
				if(FD_ISSET(0, &testfds))
				{
					ioctl(0, FIONREAD, &nread);
					if(nread == 0)
					{
						printf("keyboard done\n");
						exit(0);
					}
					nread = read(0, buffer, nread);
					buffer[nread] = 0;
					printf("read %d from ketboard: %s", nread, buffer);
				}
				break;
		}
		FD_ZERO(&inputs);
	}
}