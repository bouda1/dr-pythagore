#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include "stack.h"
#include "action.h"

using namespace std;
using namespace DP;

DP::Stack::Stack(Plane *plane)
    : _stop(false)
{
    for (int i = 0; i < NB_THREAD; i++)
        _thread[i] = thread(Action(*this, plane));
}

DP::Stack::~Stack()
{
    {
        unique_lock<mutex> lock(_stop_mutex);
        _stop = true;
    }
    _condition.notify_all();

    for (int i = 0; i < _thread.size(); i++)
        _thread[i].join();
}

DPTask *DP::Stack::dequeueTask()
{
    DPTask *retval;
    cout << "Dequeue task" << endl;
    retval = _tasks.front();
    _tasks.pop_front();
    return retval;
}

void DP::Stack::enqueueTask(DPTask *task)
{
    cout << "Enqueue task" << endl;
    {
        unique_lock<mutex> lock(_mutex);

        _tasks.push_back(task);
    }

    _condition.notify_one();
}

bool DP::Stack::queueEmpty() const
{
    return _tasks.empty();
}

bool DP::Stack::stopAsked()
{
    unique_lock<mutex> lock(_stop_mutex);
    return _stop;
}
