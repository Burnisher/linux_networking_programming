#include "sysutil.h"
#include <signal.h>
#include <pthread.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void do_service(int sockfd);

void *thread_func(void *arg);

int main(int argc, const char *argv[])
{
	if(signal(SIGCHLD, SIG_IGN) == SIG_ERR)
		ERR_EXIT("signal child");
		
	int listenfd = tcp_server("192.168.1.14", 8976);
	
	while(1)
    {
        int peerfd = accept(listenfd, NULL, NULL);
        if(peerfd == -1)
            ERR_EXIT("accept");
        printf("%s connected\n", get_tcp_info(peerfd));

        //int *pfd = (int *)malloc(sizeof(int));
        int *pfd = &peerfd;
        pthread_t tid;
        if(pthread_create(&tid, NULL, thread_func, pfd))
        {
            //free(pfd); //线程启动失败，避免内存泄露
        }
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
			printf("close...\n");
			close(sockfd);
			pthread_exit(0);
			break;
		}
		printf("receive msg: %d\n", nread);
		send_msg_with_len(sockfd, recvbuf, nread);
	}
}

void *thread_func(void *pfd)
{
	int peerfd = *(int*)pfd;
	//free(pfd);
	pthread_detach(pthread_self());
	
	do_service(peerfd);
}