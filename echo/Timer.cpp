#include "Timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/timerfd.h>
#include <stdint.h>
#include <poll.h>
#define ERR_EXIT(m) \
        do { \
                perror(m);\
                exit(EXIT_FAILURE);\
            }while(0)


namespace 
{
int createTimerfd()
{
    int timerfd = ::timerfd_create(CLOCK_REALTIME, 0);
    if(timerfd == -1)
        ERR_EXIT("timerfd_create");
    return timerfd;
}


void setTimerfd(int timerfd, int value, int interval)
{
    struct itimerspec val;
    memset(&val, 0, sizeof val);
    val.it_value.tv_sec = value;
    val.it_interval.tv_sec = interval;

    if(::timerfd_settime(timerfd, 0, &val, NULL) == -1)
    {
        ERR_EXIT("timerfd_settime");
    }
}

void stopTimerfd(int timerfd)
{
    setTimerfd(timerfd, 0, 0);
}

void readTimerfd(int timerfd)
{
    uint64_t howmany;
    if(::read(timerfd, &howmany, sizeof howmany) != sizeof(howmany))
    {
        ERR_EXIT("read timerfd error");
    }
}

}


namespace Tiny
{
Timer::Timer(int val,
             int interval,
             TimerCallback cb)
    :timerfd_(createTimerfd()),
     val_(val),
     interval_(interval),
     callback_(std::move(cb)),
     isStarted_(false)
{

}

Timer::~Timer()
{
    if(isStarted_)
    {
        stop();
    }
    ::close(timerfd_);
}

void Timer::start()
{
    setTimerfd(timerfd_, val_, interval_);
    isStarted_ = true;

    struct pollfd pfd;
    pfd.fd = timerfd_;
    pfd.events = POLLIN;

    int ret;
    while(isStarted_)
    {
        ret = ::poll(&pfd, 1, 5000);
        if(ret == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("poll");
        }
        else if(ret == 0)
        {
            printf("timeout\n");
            continue;
        }

        if(pfd.revents == POLLIN)
        {
            readTimerfd(timerfd_);
            callback_();
        }
    
    }
}

void Timer::stop()
{
    isStarted_ = false;
    stopTimerfd(timerfd_);
}
}

