#include <string>
#include "andExpr.h"

using namespace std;

DPAndExpr::DPAndExpr(BoolExpr *a, BoolExpr *b, const string &descr) :
    DPTreeBoolExpr("And", a, b, descr)
{

}

DPAndExpr::DPAndExpr(BoolExpr *a, BoolExpr *b, BoolExpr *c, const string &descr) :
    DPTreeBoolExpr("And", a, b, c, descr)
{

}

bool DPAndExpr::operator() () const
{
    for (BoolExpr *expr : *this)
        if (!(*expr)())
            return false;
    return true;
}

