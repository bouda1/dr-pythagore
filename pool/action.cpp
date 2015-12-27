#include <iostream>
#include <mutex>
#include "action.h"
#include "pool.h"

using namespace std;

DPAction::DPAction(DPPool &pool)
    : _pool(pool)
{
    cout << "Action constructor" << endl;
}

void DPAction::operator()() const
{

    while (true) {
        unique_lock<mutex> lock(_pool._mutex);

        while (!_pool._stop && _pool.queueEmpty()) {
            _pool._condition.wait(lock);
        }

        if (_pool._stop)
            return;

        DPTask *task = _pool.dequeueTask();
        task->routine();
    }
}
