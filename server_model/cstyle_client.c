#include "sysutil.h"
#define ERR_EXIT(m) \
        do { \
                perror(m);\
                exit(EXIT_FAILURE);\
           }while(0)

void do_service(int sockfd);
//void nano_sleep(double val);

int main(int argc, const char *argv[])
{
    int peerfd = tcp_client(9999);
    connect_host(peerfd, "192.168.1.26", 8976);

    printf("%s connected\n", get_tcp_info(peerfd));

    do_service(peerfd);

    close(peerfd);
    return 0;
}

void do_service(int sockfd)
{
#define SIZE 1024
    char sendbuf[SIZE] = {0};

    send_msg_with_len(sockfd, sendbuf, SIZE);
    send_msg_with_len(sockfd, sendbuf, SIZE);
    send_msg_with_len(sockfd, sendbuf, SIZE);

    //close(sockfd);
    shutdown(sockfd, SHUT_WR);

    nano_sleep(10);
    
}


