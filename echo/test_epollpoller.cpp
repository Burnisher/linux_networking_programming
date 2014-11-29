#include "Socket.h"
#include "TcpConnection.h"
#include "EpollPoller.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace Tiny;

void onConnection(const TcpConnectionPtr &conn)
{
	printf("%s\n", conn->toString().c_str());
	conn->send("hello, welcome to Chat Server.\r\n");
}

void onMessage(const TcpConnectionPtr &conn)
{
	std::string s(conn->receive());
	conn->send(s);
}

void onClose(const TcpConnectionPtr &conn)
{
	printf("%s close\n", conn->toString().c_str());
}

int main()
{
	int fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(fd == -1)
    {
        perror("create socket error");
        exit(EXIT_FAILURE);
    }
	
	InetAddress addr("192.168.1.14", 8976);
	
	Socket sock(fd);
	
	sock.setTcpNoDelay(false);
    sock.setReusePort(true);
    sock.setReuseAddr(true);
    sock.setKeepAlive(false);
	
	sock.bindAddress(addr);
	sock.listen();
	
	EpollPoller poller(fd);
	poller.setConnectCallback(&onConnection);
    poller.setMessageCallback(&onMessage);
    poller.setCloseCallback(&onClose);
	
	poller.loop();
	
	return 0;
}

