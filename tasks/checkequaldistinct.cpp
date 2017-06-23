#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "plane.h"
#include "rules/rule.h"
#include "checkequaldistinct.h"

using namespace std;

CheckEqualDistinct::CheckEqualDistinct(DPPlane *plan)
    : DPTask(), _plan(plan)
{

}

void CheckEqualDistinct::routine()
{
    cout << "CheckEqualDistinct routine" << endl;
    deque<DPRule *> mapEq = _plan->getRelations(OP_REL_EQUALS);
    deque<DPRule *>::iterator it;

    for (DPRule *r : mapEq) {
        cout << "CheckEqualDistinct CHECK" << endl;

        DPRule *rule = _plan->hasRelation(OP_REL_DISTINCT, r->get(0), r->get(1));
        if (rule) {
            cout << "<< " << r->getDescription() << " >> not compatible with << " << rule->getDescription() << " >>" << endl;
            _plan->addContradiction(r, rule);
        }
    }

}

