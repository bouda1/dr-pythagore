#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <unistd.h>
#include "plan.h"
#include "tasklua.h"

using namespace std;

DPTaskLua::DPTaskLua(DPPlan *plan, const string &filename)
    : DPTask(), _plan(plan), _L(luaL_newstate())
{
    luaL_openlibs(_L);

    if (luaL_loadfile(_L, filename.c_str()) != 0)
        cerr << "Unable to load script " << filename << endl;
    if (lua_pcall(_L, 0, 0, 0) != 0)
        cerr << "Unable to compile script " << filename << endl;
    lua_getglobal(_L, "routine");
    if (!lua_isfunction(_L,lua_gettop(_L)) )
        cerr << "Unable to find the routine function in " << filename << endl;
}

DPTaskLua::~DPTaskLua()
{
    if (_L)
        lua_close(_L);
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

