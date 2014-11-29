#include "sysutil.h"
#define ERR_EXIT(m) \
        do { \
                perror(m);\
                exit(EXIT_FAILURE);\
        }while(0)

void do_service(int sockfd);

int main(int argc, const char *argv[])
{
    int listenfd = tcp_server("192.168.1.26", 8976);

    int peerfd = accept(listenfd, NULL, NULL);

    printf("%s connected\n", get_tcp_info(peerfd));

    do_service(peerfd);

    close(peerfd);
    close(listenfd);

    return 0;
}

void do_service(int sockfd)
{
    int cnt = 0;
    char recvbuf[1024] = {0};

    while(1)
    {
        size_t nread = recv_msg_with_len(sockfd, recvbuf, sizeof recvbuf);
        if(nread == 0)
        {
            printf("close ...\n");
            break;
        }
        printf("receive msg : %d\n", nread);
        send_msg_with_len(sockfd, recvbuf, nread);
    }
    
}
