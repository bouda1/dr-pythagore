#ifndef __POOL_H__
#define __POOL_H__
#include <array>
#include <deque>
#include <condition_variable>
#include <mutex>
#include <thread>
#include "task.h"

const static int NB_THREAD = 2;

class DPPool {
    std::array<std::thread, NB_THREAD> _thread;
    std::deque<DPTask *> _tasks;
    void enqueueTask(DPTask *task);

public:
    std::condition_variable _condition;
    bool _stop;
    std::mutex _mutex;

    DPPool();
    ~DPPool();
    void loop(int time);
    DPTask *dequeueTask();
    bool queueEmpty();
};

#endif /* __POOL_H__ */


