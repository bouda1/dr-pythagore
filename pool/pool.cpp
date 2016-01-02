#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include "pool.h"
#include "action.h"

using namespace std;

DPPool::DPPool()
    : _stop(false)
{
    for (int i = 0; i < NB_THREAD; i++)
        _thread[i] = thread(DPAction(*this));
}

DPPool::~DPPool()
{
    {
        unique_lock<mutex> lock(_stop_mutex);
        _stop = true;
    }
    _condition.notify_all();

    for (int i = 0; i < _thread.size(); i++)
        _thread[i].join();
}

DPTask *DPPool::dequeueTask()
{
    DPTask *retval;
    cout << "Dequeue task" << endl;
    retval = _tasks.front();
    _tasks.pop_front();
    return retval;
}

void DPPool::enqueueTask(DPTask *task)
{
    cout << "Enqueue task" << endl;
    {
        unique_lock<mutex> lock(_mutex);

        _tasks.push_back(task);
    }

    _condition.notify_one();
}

bool DPPool::queueEmpty() const
{
    return _tasks.empty();
}

void DPPool::loop(int time)
{
    for (int i = 0; i < time; i++)
        enqueueTask(new DPTask());

    sleep(time);
}

bool DPPool::stopAsked()
{
    unique_lock<mutex> lock(_stop_mutex);
    return _stop;
}
