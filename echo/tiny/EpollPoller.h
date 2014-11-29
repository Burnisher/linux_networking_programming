#ifndef EPOLL_POLLER_H
#define EPOLL_POLLER_H

#include <boost/noncopyable.hpp>
#include <vector>
#include <map>
#include <sys/epoll.h>
#include "TcpConnection.h"

namespace Tiny
{
class EpollPoller : boost::noncopyable
{
public:
	typedef TcpConnection::TcpConnectionCallback EpollCallback;
	explicit EpollPoller(int listenfd);
	~EpollPoller();
	
	void loop();
	void unloop();
	
	void setConnectCallback(EpollCallback cb)
    { onConnectCallback_ = std::move(cb); }
    void setMessageCallback(EpollCallback cb)
    { onMessageCallback_ = std::move(cb); }
    void setCloseCallback(EpollCallback cb)
    { onCloseCallback_ = std::move(cb); }
	
private:
	void waitEpollFd();
	void handleConnection();
	void handleMessage(int peerfd);
	
	const int epollfd_;
	const int listenfd_;
	bool isLooping_;
	
	typedef std::vector<struct epoll_event> EventList;
	EventList events_;
	
	typedef std::map<int, TcpConnectionPtr> ConnectionList;
	ConnectionList lists_;
	
	EpollCallback onConnectCallback_;
	EpollCallback onMessageCallback_;
	EpollCallback onCloseCallback_;
};

}

#endif //EPOLL_POLLER_H