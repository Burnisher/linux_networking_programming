#include "Socket.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(fd == -1)
    {
        perror("create socket error");
        exit(EXIT_FAILURE);
    }

    InetAddress addr("192.168.1.14", 9981);

    Socket sock(fd);

    sock.setTcpNoDelay(false);
    sock.setReusePort(true);
    sock.setReuseAddr(true);
    sock.setKeepAlive(false);

    sock.bindAddress(addr);
    sock.listen();

    int peerfd = sock.accept();
	
	InetAddress localaddress = Socket::getLocalAddress(peerfd);
	InetAddress peeraddress = Socket::getPeerAddress(peerfd);
	std::string ls = localaddress.toIp();
	std::string ps = peeraddress.toIp();
	printf("laddress : %s\n", ls.c_str());
	printf("paddress : %s\n", ps.c_str());
	

    while(1)
    {
        char recvbuf[1024] = {0};
        ::read(peerfd, recvbuf, sizeof recvbuf);
        printf("receive msg : %s", recvbuf);
        ::write(peerfd, recvbuf, strlen(recvbuf));
    }


    return 0;
}