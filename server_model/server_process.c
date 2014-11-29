#include "sysutil.h"
#include <signal.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void do_service(int sockfd);

int main(int argc, const char *argv[])
{
	if(signal(SIGCHLD, SIG_IGN) == SIG_ERR)
		ERR_EXIT("signal child");
	
	int listenfd = tcp_server("192.168.1.26", 8976);
	
	while(1)
	{
		int peerfd = accept(listenfd, NULL, NULL);
		if(peerfd == -1)
			ERR_EXIT("accept");
		printf("%s connected\n", get_tcp_info(peerfd));
		
		pid_t pid = fork();
		if(pid == -1)
			ERR_EXIT("fork");
		else if(pid == 0)
		{
			close(listenfd);
			do_service(peerfd);
			exit(EXIT_SUCCESS);
		}
		close(peerfd);
	}
	
	close(listenfd);
	
	return 0;
}

void do_service(int sockfd)
{
    char recvbuf[1024] = {0};

    while(1)
    {
        size_t nread = recv_msg_with_len(sockfd, recvbuf, sizeof recvbuf);
        if(nread == 0)
        {
            printf("close ...\n");
            close(sockfd);
            exit(EXIT_SUCCESS);
            break;
        }
        printf("receive msg : %d\n", nread);
        send_msg_with_len(sockfd, recvbuf, nread);
    }
}