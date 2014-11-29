#include "TimerThread.h"

namespace Tiny
{
TimerThread::TimerThread(int value,
                         int interval,
                         Callback cb)
    :timer_(value, interval, std::move(cb)),
     thread_(std::bind(&Timer::start, &timer_))
{

}

void TimerThread::start()
{
    thread_.start();
}

void TimerThread::stop()
{
    timer_.stop();
    thread_.join();
}
}


