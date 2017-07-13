#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "plane.h"
#include "checklinesequality.h"

using namespace std;

CheckLinesEquality::CheckLinesEquality(Plane *plan)
    : DPTask(), _plan(plan)
{
}

void CheckLinesEquality::routine(lua_State *L)
{
    cout << "CheckLinesEquality routine" << endl;
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

