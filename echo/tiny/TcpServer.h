#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include <boost/noncopyable.hpp>
#include "EpollPoller.h"
#include "Socket.h"

namespace Tiny
{
class TcpServer : boost::noncopyable
{
public:
	typedef TcpConnection::TcpConnectionCallback TcpServerCallback;
	
	explicit TcpServer(const InetAddress &addr);
	
	void start()
	{ poller_.loop(); }
	
	void setConnectCallback(TcpServerCallback cb)
	{ poller_.setConnectCallback(std::move(cb)); }
	void setMessageCallback(TcpServerCallback cb)
    { poller_.setMessageCallback(std::move(cb)); }
    void setCloseCallback(TcpServerCallback cb)
    { poller_.setCloseCallback(std::move(cb)); }
	
private:
	Socket sockfd_;
	EpollPoller poller_;
};

}


#endif //TCP_SERVER_H_