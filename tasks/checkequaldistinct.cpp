#include <sstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "plane.h"
#include "boolExpr.h"
#include "simpleExpr.h"
#include "checkequaldistinct.h"

using namespace std;
using namespace DP;

CheckEqualDistinct::CheckEqualDistinct(Plane *plan)
    : DPTask(), _plan(plan)
{

}

void CheckEqualDistinct::routine(lua_State *L)
{
    cout << "CheckEqualDistinct routine" << endl;
    deque<DP::BoolExpr *> mapEq = _plan->getExprs("Equals");
    deque<DP::BoolExpr *>::iterator it;

    for (BoolExpr *r : mapEq) {
        SimpleExpr *simp = dynamic_cast<SimpleExpr *>(r);
        if (simp) {
            cout << "CheckEqualDistinct CHECK" << endl;

            BoolExpr *expr = _plan->hasExpr("Distinct", simp->at(0), simp->at(1));
            if (expr) {
                stringstream ss;
                ss << "<< " << r->getDescr() << " >> not compatible with << " << expr->getDescr() << " >>";
                string err = ss.str();
                _plan->addContradiction(err);
            }
        }
    }
}

