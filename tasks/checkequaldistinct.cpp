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
    deque<DPTRule> mapEq = _plan->getRelations(BIN_REL_EQUALS);
    deque<DPTRule>::iterator it;

    for (it = mapEq.begin(); it != mapEq.end(); ++it) {
        cout << "CheckEqualDistinct CHECK" << endl;

        DPTRule *rule = _plan->hasRelation(BIN_REL_DISTINCT, get<1>(*it), get<2>(*it));
        if (rule) {
            cout << "PROBLEM: " << get<3>(*it) << endl;
            cout << "\tand " << get<3>(*rule) << endl;
            abort();
        }
    }

}

