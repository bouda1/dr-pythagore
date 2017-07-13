#include <iostream>
#include <mutex>
#include "action.h"
#include "stack.h"
#include "plane_binding.h"

using namespace std;
using namespace DP;

Action::Action(Stack &stack, Plane *plane)
    : _stack(stack), _plane(plane), _L(NULL)
{
    cout << "Action constructor" << endl;
}

Action::~Action()
{
    if (_L)
        lua_close(_L);
}

void Action::operator()()
{
    cout << "Lua state initialization" << endl;
    _L = luaL_newstate();
    luaL_openlibs(_L);
    registerPlane(_L, _plane);

    while (true) {
        unique_lock<mutex> lock(_stack._mutex);

        while (!_stack.stopAsked() && _stack.queueEmpty()) {
            _stack._condition.wait(lock);
        }

        if (_stack.stopAsked())
            return;

        DPTask *task = _stack.dequeueTask();
        task->routine(_L);
    }
}
