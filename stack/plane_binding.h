#if !defined __PLANE_BINDING_H__
#define __PLANE_BINDING_H__
#include "plane.h"

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

void registerPlane(lua_State *L, DPPlane *plane);


#endif // __PLANE_BINDING_H__
