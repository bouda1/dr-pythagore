/* Dr-Pythagore 
 * Copyright (C) 2016-2017 D. Boucher
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <sys/types.h>
#include <cerrno>
#include <dirent.h>
#include <sstream>
#include <iostream>
#include <string>
#include <cstring>
//#include <lauxlib.h>
#include "plane_binding.h"
#include "plane.h"
#include "point.h"
#include "simpleExpr.h"


using namespace std;
using namespace DP;

DP::Plane *l_CheckPlane(lua_State *L, int n)
{
    return *(DP::Plane **)luaL_checkudata(L, n, "luaL_Plane");
}
 
void stackDump(lua_State *L)
{
    int i;
    int top = lua_gettop(L);
    for (i = 1; i <= top; ++i) {  /* repeat for each level */
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

int l_getExprs(lua_State *L)
{
    DP::Plane *plane = l_CheckPlane(L, 1);
    const char *op = luaL_checkstring(L, 2);
    deque<DP::BoolExpr *> exprs;

    if (string(op) == "Aligned")
        exprs = plane->getExprs("Aligned");
    else if (string(op) == "NotAligned")
        exprs = plane->getExprs("Not", "Aligned");
    else if (string(op) == "Equals")
        exprs = plane->getExprs("Equals");
    else if (string(op) == "Distinct")
        exprs = plane->getExprs("Distinct");

    lua_createtable(L, exprs.size(), 0);
    int count = 1;
    for (DP::BoolExpr *r : exprs) {
        SimpleExpr *simp = dynamic_cast<SimpleExpr *>(r);
        if (simp) {
            lua_createtable(L, simp->size(), 0);
            int cc = 1;
            for (DP::Element *e : *simp) {
                lua_pushstring(L, e->getName().c_str());
                lua_rawseti(L, -2, cc++);
            }
            lua_rawseti(L, -2, count++);
        }
    }
 
    return 1;
}
 
int l_setPointRelation(lua_State *L)
{
    stackDump(L);
    DP::Plane *plane = l_CheckPlane(L, 1);
    const char *op = luaL_checkstring(L, 2);
    const char *a = luaL_checkstring(L, 3);
    const char *b = luaL_checkstring(L, 4);
    //const char *c = luaL_checkstring(L, 5);

    DP::Point *aa = plane->getPoint(a);
    DP::Point *bb = plane->getPoint(b);
    //DPPoint *cc;
    //if (c)
    //    cc = plane->getPoint(c);
    //else
    //    cc = nullptr;

    if (!aa || !bb) {
        cerr << a << " and " << b << " are not defined" << endl;
        return 0;
    }
    if (string(op) == "Distinct") {
        stringstream ss;
        ss << a << " and " << b << " are distinct.";
        cout << ss.str() << endl;
        SimpleExpr *simp = new SimpleExpr("Distinct", aa, bb, ss.str());
        plane->addExpression(simp);
    }
    else {
        cerr << "Cannot understand operator " << op << endl;
    }
    return 0;
}

int l_Plane_destructor(lua_State *L)
{
    cout << "Plane destructor" << endl;
    /*DP::Plane *plane = */l_CheckPlane(L, 1);
 
    return 0;
}
 
int parseLuaScripts(lua_State *L, const string &dir)
{
    struct dirent *dirp;
    DIR *dp = opendir(dir.c_str());
    if (dp == NULL) {
        cerr << "ERROR: " << errno << " while opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp))) {
        char *str = dirp->d_name;
        if (strlen(str) > 4 && !strcmp(str + strlen(str) - 4, ".lua")) {
            cout << "Reading " << str << "..." << endl;
            if (luaL_loadfile(L, str) != 0) {
                cerr << "Unable to load file " << str << endl;
                return -1;
            }
            if (lua_pcall(L, 0, 0, 0) != 0) {
                cerr << "Unable to compile file " << str << endl;
                return -2;
            }
        }
    }
    closedir(dp);
    return 0;
}

void registerPlane(lua_State *L, DP::Plane *plane)
{
    DP::Plane **udata = static_cast<DP::Plane **>(lua_newuserdata(L, sizeof(DP::Plane *)));
    *udata = plane;

    luaL_Reg sPlaneRegs[] =
    {
        { "getRelations", l_getExprs },
        { "setPointRelation", l_setPointRelation },
        { "__gc", l_Plane_destructor },
        { NULL, NULL }
    };
 
    // Create a luaL metatable. This metatable is not 
    // exposed to Lua. The "luaL_Plane" label is used by luaL
    // internally to identity things.
    luaL_newmetatable(L, "luaL_Plane");
 
    // Register the C functions _into_ the metatable we just created.
#ifdef LUA51
    luaL_register(L, NULL, sPlaneRegs);
#else
    luaL_setfuncs(L, sPlaneRegs, 0);
#endif

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

    parseLuaScripts(L, ".");

}

