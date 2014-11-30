#include "ChatServer.h"
using namespace Tiny;

int main(int argc, char const *argv[])
{
    ChatServer server(InetAddress("192.168.1.15", 9981));
    server.start();
    return 0;
}
