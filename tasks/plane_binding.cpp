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
 
int l_getRelations(lua_State *L)
{
    DPPlane *plane = l_CheckPlane(L, 1);
    const char *op = luaL_checkstring(L, 2);
    deque<DPRule *> rules;

    if (string(op) == "Aligned") {
        cout << "COOL, I known Aligned" << endl;
        rules = plane->getRelations(BIN_REL_ALIGNED);
        lua_createtable(L, rules.size(), 0);
        int count = 1;
        for (DPRule *r : rules) {
            lua_pushstring(L, r->getDescription().c_str());
            lua_rawseti(L, -2, count++);
        }
    }
    //std::string s = foo->Add(a, b);
    //lua_pushstring(L, s.c_str());
 
    // FIXME DBR : reste à pousser retval dans un tableau lua
    //
    // The Lua stack at this point looks like this:
    //     
    //     4| result string          |-1
    //     3| metatable "luaL_foo"   |-2
    //     2| userdata               |-3
    //     1| string parameter       |-4
    //
    // Return 1 to return the result string to Lua callsite.
 
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
    //     1| metatable "luaL_Foo"   |-1
    lua_pushvalue(L, -1);
 
    // The Lua stack at this point looks like this:
    //     
    //     2| metatable "luaL_Foo"   |-1
    //     1| metatable "luaL_Foo"   |-2
 
    // Set the "__index" field of the metatable to point to itself
    // This pops the stack
    lua_setfield(L, -1, "__index");
 
    // The Lua stack at this point looks like this:
    //     
    //     1| metatable "luaL_Foo"   |-1
 
    // The luaL_Plane metatable now has the following fields
    //     - __gc
    //     - __index
    //     - getRelations
 
    // Now we use setglobal to officially expose the luaL_Plane metatable
    // to Lua. And we use the name "Foo".
    //
    // This allows Lua scripts to _override_ the metatable of Foo.
    // For high security code this may not be called for but 
    // we'll do this to get greater flexibility.
    //lua_setglobal(L, "Plane");

    lua_setmetatable(L, -2);
    lua_setglobal(L, "Plane");
}
 
