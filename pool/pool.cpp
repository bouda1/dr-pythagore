#include <iostream>
#include <thread>
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
    _stop = true;
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

bool DPPool::queueEmpty()
{
    cout << "queue Empty ?" << endl;
    return _tasks.empty();
}

void DPPool::loop(int time)
{
    int i;

    for (i = 0; i < time; i++) {
        enqueueTask(new DPTask());
    }
    sleep(time);
}

int main()
{
    DPPool pool;
    pool.loop(10);
    cout << "This is the end" << endl;
    return 0;
}