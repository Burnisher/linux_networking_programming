#include "TcpServer.h"

namespace
{
int createSockfd()
{
	int fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(fd == -1)
	{
		fprintf(stderr, "create socket fd error.\n");
		exit(EXIT_FAILURE);
	}
	return fd;
}
	
}

namespace Tiny
{
TcpServer::TcpServer(const InetAddress &addr)
	:sockfd_(createSockfd()),
	 poller_(sockfd_.fd())
{
	sockfd_.setTcpNoDelay(false);
	sockfd_.setReusePort(true);
    sockfd_.setReuseAddr(true);
    sockfd_.setKeepAlive(false);
	
	sockfd_.bindAddress(addr);
	sockfd_.listen();
}

}