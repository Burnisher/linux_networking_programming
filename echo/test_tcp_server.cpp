#include "TcpServer.h"
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

int main(int argc, const char *argv[])
{
	InetAddress addr("192.168.1.14", 8976);
	TcpServer server(addr);
	
	server.setConnectCallback(&onConnection);
    server.setMessageCallback(&onMessage);
    server.setCloseCallback(&onClose);
	
	server.start();
	
	return 0;
}