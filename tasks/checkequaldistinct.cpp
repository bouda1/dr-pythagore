#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "plan.h"
#include "checkequaldistinct.h"

using namespace std;

CheckEqualDistinct::CheckEqualDistinct(DPPlan *plan)
    : DPTask(), _plan(plan)
{

}

void CheckEqualDistinct::routine()
{
    cout << "CheckEqualDistinct routine" << endl;
    unordered_map<DPElement *, unordered_set<DPElement *> > mapEq = _plan->getRelations(BIN_REL_EQUALS);
    unordered_map<DPElement *, unordered_set<DPElement *> >::iterator it;
    unordered_set<DPElement *>::iterator sit;

    for (it = mapEq.begin(); it != mapEq.end(); ++it) {
        cout << "CheckEqualDistinct CHECK" << endl;
        DPElement *el = it->first;

        for (sit = it->second.begin(); sit != it->second.end(); ++sit) {
            if (_plan->hasRelation(BIN_REL_DISTINCT, el, *sit)) {
                cout << "PROBLEM..." << endl;
                abort();
            }
        }
    }

}

