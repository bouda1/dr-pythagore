#ifndef __TASKLUA_H__
#define __TASKLUA_H__
#include "task.h"

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

class DPPlan;

class DPTaskLua: public DPTask {
    DPPlan *_plan;
    lua_State *_L;

public:
    virtual void routine();
    DPTaskLua(DPPlan *plan, const std::string &filename);
    ~DPTaskLua();
};

#endif /* __TASKLUA_H__ */
