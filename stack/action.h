#ifndef __ACTION_H__
#define __ACTION_H__

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

class DPStack;
class DPPlane;

class DPAction {
    DPStack &_stack;
    DPPlane *_plane;
    lua_State *_L;

public:
    DPAction(DPStack &stack, DPPlane *plane);
    ~DPAction();

    void operator()();
};

#endif /* __ACTION_H__ */
