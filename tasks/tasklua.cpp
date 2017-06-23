#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <unistd.h>
#include "plane.h"
#include "tasklua.h"
#include "plane_binding.h"

using namespace std;

DPTaskLua::DPTaskLua(DPPlane *plan, const string &filename)
    : DPTask(), _plan(plan), _L(luaL_newstate())
{
    luaL_openlibs(_L);
    RegisterPlane(_L, _plan);

    if (luaL_loadfile(_L, filename.c_str()) != 0)
        cerr << "Unable to load script " << filename << endl;
    if (lua_pcall(_L, 0, 0, 0) != 0)
        cerr << "Unable to compile script " << filename << endl;
    lua_getglobal(_L, "routine");
    if (!lua_isfunction(_L,lua_gettop(_L)) )
        cerr << "Unable to find the routine function in " << filename << endl;
    //lua_pushcfunction(_L, DPTaskLua::l_getElementsByOp);
    //lua_setglobal(_L, "getElementsByOp");

}

DPTaskLua::~DPTaskLua()
{
    if (_L)
        lua_close(_L);
}

int DPTaskLua::l_getElementsByOp(lua_State *L)
{
    string op = string(lua_tostring(L, 1));  /* get argument */
    if (op == "Aligned")
        lua_pushstring(L, "You want ALIGNED elements !");
    return 1;  /* number of results */
}

void DPTaskLua::routine()
{
    cout << "TaskLua routine" << endl;
    lua_getglobal(_L, "routine");
    lua_pcall(_L, 0, 0, 0);
//    cout << "Check if two parallel lines share a point - in that case, all points from one are added to the other and vice versa." << endl;
//    unordered_map<DPElement *, unordered_set<DPElement *> > mapParal = _plan->getRelations(BIN_REL_PARALLEL);
//    unordered_map<DPElement *, unordered_set<DPElement *> > mapEqual = _plan->getRelations(BIN_REL_EQUALS);
//    unordered_map<DPElement *, unordered_set<DPElement *> >::iterator it;
//    unordered_set<DPElement *>::iterator sit;
//
//    for (it = mapParal.begin(); it != mapParal.end(); ++it) {
//        DPLine *first = reinterpret_cast<DPLine *>(it->first);
//        unordered_set<DPPoint *> set = second->getSinglePoints();
//
//        for (sit = it->second.begin(); sit != it->second.end(); ++sit) {
//            for (DPPoint *point : set) {
//                if (sit->contains(point)) {
//                    /* Lines are parallele and share a point : they are equal */
//                    _plan->setRelation(BIN_REL_EQUALS, first, 
//                }
//            }
//            DPLine *second = reinterpret_cast<DPLine *>(*sit);
//
//            
//        }
//    }

}

