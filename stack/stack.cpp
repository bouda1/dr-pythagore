#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include "stack.h"
#include "action.h"

using namespace std;

DPStack::DPStack(DPPlane *plane)
    : _stop(false)
{
    for (int i = 0; i < NB_THREAD; i++)
        _thread[i] = thread(DPAction(*this, plane));
}

DPStack::~DPStack()
{
    {
        unique_lock<mutex> lock(_stop_mutex);
        _stop = true;
    }
    _condition.notify_all();

    for (int i = 0; i < _thread.size(); i++)
        _thread[i].join();
}

DPTask *DPStack::dequeueTask()
{
    DPTask *retval;
    cout << "Dequeue task" << endl;
    retval = _tasks.front();
    _tasks.pop_front();
    return retval;
}

void DPStack::enqueueTask(DPTask *task)
{
    cout << "Enqueue task" << endl;
    {
        unique_lock<mutex> lock(_mutex);

        _tasks.push_back(task);
    }

    _condition.notify_one();
}

bool DPStack::queueEmpty() const
{
    return _tasks.empty();
}

bool DPStack::stopAsked()
{
    unique_lock<mutex> lock(_stop_mutex);
    return _stop;
}
