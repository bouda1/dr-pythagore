#ifndef __TASK_H__
#define __TASK_H__

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

class DPTask {
public:
    virtual void routine(lua_State *L) = 0;
};

#endif /* __TASK_H__ */

