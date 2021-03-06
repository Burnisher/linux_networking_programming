#ifndef SOCKETIO_H_
#define SOCKETIO_H_

#include <boost/noncopyable.hpp>
#include <sys/types.h>

namespace Tiny
{
class SocketIO : boost::noncopyable
{
public:
	explicit SocketIO(int sockfd)
		:sockfd_(sockfd)
	{	
	}
		
	ssize_t readn(char *buf, size_t count);
	ssize_t writen(const char *buf, size_t count);
	ssize_t readLine(char *usrbuf, size_t maxlen);
private:
	ssize_t recv_peek(char *buf, size_t len);
	
	const int sockfd_;
};


}

#endif //SOCKETIO_H_