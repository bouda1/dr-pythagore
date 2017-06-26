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
    DPPlane *_plane;
    lua_State *_L;

public:
    virtual void routine(lua_State *L);
    DPTaskLua(DPPlane *plan, const std::string &filename);
    ~DPTaskLua();
};

#endif /* __TASKLUA_H__ */
