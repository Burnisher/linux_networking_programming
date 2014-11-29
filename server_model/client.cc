#include "def.h"
#include <sys/select.h>
#include <iostream>
/*
 * 
 *
 */
using namespace std;
 
void do_service(int peerfd);
 
int main(int argc, const char *argv[])
{
    //1.创建 socket
    int peerfd = socket(AF_INET, SOCK_STREAM, 0);
    if(peerfd == -1)
        ERR_EXIT("socket");
 
   //2. conncet
    struct sockaddr_in  peeraddr;
    peeraddr.sin_family = AF_INET;
    peeraddr.sin_addr.s_addr = inet_addr("192.168.1.14");
    peeraddr.sin_port = htons(8976);
    if(connect(peerfd, (struct sockaddr*)&peeraddr, sizeof(peeraddr)) == -1)
        ERR_EXIT("connect");
 
    do_service(peerfd);
 
    close(peerfd);
    return 0;
}
 
void do_service(int peerfd){
    char sendbuf[1024] = {0};
    char recvbuf[1024] = {0};
 
    //1.初始化数组，添加要监听的描述符
    fd_set read_set, ready_set;
    FD_ZERO(&read_set);
    FD_SET(STDIN_FILENO, &read_set);
    FD_SET(peerfd, &read_set);
 
    int maxfd = STDIN_FILENO > peerfd ? STDIN_FILENO : peerfd;
    int nready; //接收select的返回值
 
    // 2.执行监听
    while(1){
        ready_set = read_set;
        nready = select(maxfd + 1, &ready_set, NULL, NULL, NULL);
        if(nready == -1){
            if(errno == EINTR)
                continue;
            ERR_EXIT("select");
        }
        else if(nready == 0)
            continue;
        // 3.依次检查每个fd是否在集合中
        if(FD_ISSET(STDIN_FILENO, &ready_set)){
            if(fgets(sendbuf, sizeof(sendbuf), stdin) == NULL){
                shutdown(peerfd, SHUT_WR);
                //从监听集合中移除该fd
                FD_CLR(STDIN_FILENO, &read_set);
            }
			cout << "sendmsg:" << sendbuf;
            writen(peerfd, sendbuf, strlen(sendbuf));
        }
 
        if(FD_ISSET(peerfd, &ready_set)){
            int ret = readline(peerfd, recvbuf, sizeof(recvbuf));
            if(ret == -1)
                ERR_EXIT("readline");
            else if(ret == 0){
                close(peerfd);
                printf("server closed\n");
                break;
            }
            printf("recv data: %s", recvbuf);
			memset(recvbuf, 0, sizeof recvbuf);
        }
    }
}
