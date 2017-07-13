#include <string>
#include "orExpr.h"

using namespace std;

DPOrExpr::DPOrExpr(BoolExpr *a, BoolExpr *b, const string &descr) :
    DPTreeBoolExpr("Or", a, b, descr)
{

}

DPOrExpr::DPOrExpr(BoolExpr *a, BoolExpr *b, BoolExpr *c, const string &descr) :
    DPTreeBoolExpr("Or", a, b, c, descr)
{

}

bool DPOrExpr::operator() () const
{
    for (BoolExpr *expr : *this)
        if ((*expr)())
            return true;
    return false;
}
