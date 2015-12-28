#ifndef __POOL_H__
#define __POOL_H__
#include <array>
#include <deque>
#include <condition_variable>
#include <mutex>
#include <thread>
#include "action.h"
#include "task.h"

const static int NB_THREAD = 2;

class DPPool {
    std::array<std::thread, NB_THREAD> _thread;
    std::deque<DPTask *> _tasks;
    bool _stop;
    void enqueueTask(DPTask *task);
    std::condition_variable _condition;
    std::mutex _mutex;

public:
    friend void DPAction::operator()() const;

    DPPool();
    ~DPPool();
    void loop(int time);
    DPTask *dequeueTask();
    bool queueEmpty() const;
    bool stopAsked() const;
};

#endif /* __POOL_H__ */

