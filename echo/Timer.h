#ifndef TIMER_H_
#define TIMER_H_

#include <boost/noncopyable.hpp>
#include <sys/timerfd.h>
#include <functional>

namespace Tiny
{
class Timer : boost::noncopyable
{
public:
    typedef std::function<void ()> TimerCallback;

    Timer(int val,
          int interval,
          TimerCallback cb);
    ~Timer();

    void start();
    void stop();
private:
    int timerfd_;
    int val_;
    int interval_;
    TimerCallback callback_;
    bool isStarted_;
};
}

#endif //TIMER_H_
