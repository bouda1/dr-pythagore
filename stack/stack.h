#ifndef __POOL_H__
#define __POOL_H__
#include <array>
#include <deque>
#include <condition_variable>
#include <mutex>
#include <thread>
#include "action.h"
#include "task.h"

class DPRule;

const static int NB_THREAD = 2;

class DPStack {
    std::array<std::thread, NB_THREAD> _thread;
    std::deque<DPTask *> _tasks;
    bool _stop;
    std::mutex _stop_mutex;

    std::condition_variable _condition;
    std::mutex _mutex;

public:
    friend void DPAction::operator()();

    DPStack(DPPlane *plane);
    ~DPStack();
    DPTask *dequeueTask();
    bool queueEmpty() const;
    bool stopAsked();
    void enqueueTask(DPTask *task);
};

#endif /* __POOL_H__ */

