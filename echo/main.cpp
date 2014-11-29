#include "ThreadPool.h"
#include "TimerThread.h"
#include <time.h>
#include <stdio.h>
#include <errno.h>
using namespace Tiny;

void nano_sleep(double val);

void foo()
{
    printf("foo\n");
}

void stopPool(ThreadPool *pool)
{
    pool->stop();
}

int main(int argc, const char *argv[])
{
    Tiny::ThreadPool pool(100, 4);
    Tiny::TimerThread timer(3, 0, std::bind(&stopPool, &pool));

    pool.start();
    timer.start();

    while(pool.isStarted())
    {
        pool.addTask(&foo);
        nano_sleep(0.5);
    }

    timer.stop();
    pool.stop();

    return 0;
}

//精确到纳秒
void nano_sleep(double val)
{
    struct timespec tv;
    tv.tv_sec = val; //取整
    tv.tv_nsec = (val - tv.tv_sec) * 1000 * 1000 * 1000;

    int ret;
    do
    {
        ret = nanosleep(&tv, &tv);
    }while(ret == -1 && errno == EINTR);
}
