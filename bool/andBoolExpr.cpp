#include <iostream>
#include "andBoolExpr.h"

using namespace std;
using namespace DP;

AndBoolExpr::AndBoolExpr(BoolExpr *a, BoolExpr *b, const string &descr)
    : TreeBoolExpr("And", a, b, descr)
{

}

bool AndBoolExpr::operator()() const
{
    for (BoolExpr *e : *this) {
        if (!(*e)())
            return false;
    }
    return true;
}

string AndBoolExpr::getString()
{
    cout << '(' << at(0)->getString() << ") And (" << at(1)->getString() << ')';
}
