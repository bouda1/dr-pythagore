#include <iostream>
#include <string>
#include "plane_binding.h"
#include "plane.h"
#include "rules/rule.h"

using namespace std;

//  https://gist.github.com/kizzx2/5221139

DPPlane *l_CheckPlane(lua_State *L, int n)
{
    // This checks that the argument is a userdata 
    // with the metatable "luaL_Plane"
    return *(DPPlane **)luaL_checkudata(L, n, "luaL_Plane");
}
 
static void stackDump(lua_State *L)
{
    int i;
    int top = lua_gettop(L);
    for (i = 1; i <= top; i++) {  /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {

            case LUA_TSTRING:  /* strings */
                cout << "`" << lua_tostring(L, i) << "'";
                break;

            case LUA_TBOOLEAN:  /* booleans */
                cout << (lua_toboolean(L, i) ? "true" : "false");
                break;

            case LUA_TNUMBER:  /* numbers */
                cout << lua_tonumber(L, i);
                break;

            default:  /* other values */
                cout << lua_typename(L, t);
                break;

        }
        cout << "  ";  /* put a separator */
    }
    cout << endl;  /* end the listing */
}

int l_getRelations(lua_State *L)
{
    DPPlane *plane = l_CheckPlane(L, 1);
    const char *op = luaL_checkstring(L, 2);
    deque<DPRule *> rules;

    if (string(op) == "Aligned")
        rules = plane->getRelations(OP_REL_ALIGNED);
    else if (string(op) == "NotAligned")
        rules = plane->getRelations(OP_REL_NOTALIGNED);

    lua_createtable(L, rules.size(), 0);
    int count = 1;
    for (DPRule *r : rules) {
        list<DPElement *> lst = r->getElements();
        lua_createtable(L, lst.size(), 0);
        int cc = 1;
        for (DPElement *e : lst) {
            lua_pushstring(L, e->getName().c_str());
            lua_rawseti(L, -2, cc++);
        }
        lua_rawseti(L, -2, count++);
    }
 
    return 1;
}
 
int l_Plane_destructor(lua_State *L)
{
    cout << "Plane destructor" << endl;
    DPPlane *plane = l_CheckPlane(L, 1);
    delete plane;
 
    return 0;
}
 
void RegisterPlane(lua_State *L, DPPlane *plane)
{
    DPPlane **udata = static_cast<DPPlane **>(lua_newuserdata(L, sizeof(DPPlane *)));
    *udata = plane;

    luaL_Reg sPlaneRegs[] =
    {
        { "getRelations", l_getRelations },
        { "__gc", l_Plane_destructor },
        { NULL, NULL }
    };
 
    // Create a luaL metatable. This metatable is not 
    // exposed to Lua. The "luaL_Plane" label is used by luaL
    // internally to identity things.
    luaL_newmetatable(L, "luaL_Plane");
 
    // Register the C functions _into_ the metatable we just created.
    luaL_register(L, NULL, sPlaneRegs);
 
    // The Lua stack at this point looks like this:
    //     
    //     1| userdata               |-2
    //     2| metatable "luaL_Foo"   |-1
    lua_pushvalue(L, -1);
 
    // The Lua stack at this point looks like this:
    //     
    //     1| userdata               |-3
    //     2| metatable "luaL_Foo"   |-2
    //     3| metatable "luaL_Foo"   |-1
 
    // Set the "__index" field of the metatable to point to itself
    // This pops the stack
    lua_setfield(L, -1, "__index");
 
    // The Lua stack at this point looks like this:
    //     
    //     1| userdata               |-2
    //     2| metatable "luaL_Foo"   |-1
 
    // The luaL_Plane metatable now has the following fields
    //     - __gc
    //     - __index
    //     - getRelations
 
    // Now, we use setmetatable to set it to our userdata
    lua_setmetatable(L, -2);

    // And now, we use setglobal to store userdata as the variable Plane.
    lua_setglobal(L, "Plane");
}
 
