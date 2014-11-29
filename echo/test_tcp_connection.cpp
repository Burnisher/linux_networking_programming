#include "Socket.h"
#include "TcpConnection.h"
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

    Tiny::InetAddress addr("192.168.1.14", 8976);

    Tiny::Socket sock(fd);

    sock.setTcpNoDelay(false);
    sock.setReusePort(true);
    sock.setReuseAddr(true);
    sock.setKeepAlive(false);

    sock.bindAddress(addr);
    sock.listen();

    int peerfd = sock.accept();

    Tiny::TcpConnectionPtr conn(new Tiny::TcpConnection(peerfd));

    while(1)
    {
        std::string msg(conn->receive());
        conn->send(msg);
    }

    conn->shutdown();
    ::close(fd);

    return 0;
}