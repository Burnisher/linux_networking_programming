#include "def.h"
#include <iostream>
using namespace std;

int listenfd_init();//返回一个处于监听状态的套接字描述符
void do_serverice(int peerfd);//处理客户端的请求

int main(int argc, const char *argv[])
{
	if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		ERR_EXIT("signal");
	int listenfd = listenfd_init();
	struct sockaddr_in peeraddr;
	socklen_t len = sizeof(peeraddr);
	int peerfd;
	while(1)
	{
		if(peerfd = accept(listenfd, (struct sockaddr*)&peeraddr, &len) == -1)
			ERR_EXIT("accept");
		cout << "connection constructed" << endl;
		do_serverice(peerfd);
		cout << "connection detached" << endl;
		close(peerfd);
	}
	close(listenfd);
	return 0;
}

int listenfd_init()
{
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	int on = 1;
	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(9999);
	if(listenfd == -1)
		ERR_EXIT("socket");
	if(bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) == -1)
		ERR_EXIT("bind");
	if(listen(listenfd, 10) == -1)
		ERR_EXIT("listen");
	return listenfd;
}

void do_serverice(int peerfd)
{
	cout << "server begin" << endl;
	char recvbuf[1024] = {0};
	int ret;
	while(1)
	{
		ret = readline(peerfd, recvbuf, 1024);
		cout << ret << endl;
		if(ret <= 0)
			break;
		printf("recv data: %s", recvbuf);
		writen(peerfd, recvbuf, strlen(recvbuf));
	}
}
