#ifndef __TASKLUA_H__
#define __TASKLUA_H__
#include "task.h"

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

class DPPlane;

class DPTaskLua: public DPTask {
    DPPlane *_plan;
    lua_State *_L;

    static int l_getElementsByOp(lua_State *L);

public:
    virtual void routine();
    DPTaskLua(DPPlane *plan, const std::string &filename);
    ~DPTaskLua();
};

#endif /* __TASKLUA_H__ */
