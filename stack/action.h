#ifndef __ACTION_H__
#define __ACTION_H__

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

namespace DP {
class Stack;
class Plane;

class Action {
    Stack &_stack;
    Plane *_plane;
    lua_State *_L;

public:
    Action(Stack &stack, Plane *plane);
    ~Action();

    void operator()();
};
}
#endif /* __ACTION_H__ */
