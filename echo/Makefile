.PHONY:clean
CC=g++
CFLAGS=-Wall -g -std=c++0x
BIN=libtiny.a
OBJS=MutexLock.o Condition.o \
	 Thread.o Timer.o \
	 ThreadPool.o TimerThread.o \
	 InetAddress.o Socket.o \
	 SocketIO.o  TcpConnection.o \
	 EpollPoller.o TcpServer.o
$(BIN):$(OBJS)
	ar -crv $@ -o $^
	chmod +x $@
	mkdir tiny
	cp *h tiny/
%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN) core -r tiny
