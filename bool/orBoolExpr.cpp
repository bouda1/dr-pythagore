#include <list>
#include <vector>
#include <iostream>
#include <sstream>
#include "orBoolExpr.h"
#include "boolTable.h"

using namespace std;
using namespace DP;

OrBoolExpr::OrBoolExpr(BoolExpr *a, BoolExpr *b, const string &descr)
    : TreeBoolExpr("Or", a, b, descr)
{

}

bool OrBoolExpr::operator()() const
{
    for (BoolExpr *e : *this) {
        if ((*e)())
            return true;
    }
    return false;
}

string OrBoolExpr::getString()
{
    stringstream ss;
    ss << '(' << at(0)->getString() << ") Or (" << at(1)->getString() << ')';
    return ss.str();
}

bool OrBoolExpr::fillResult(BoolTable &table, unsigned long input)
{
    for (BoolExpr *e : *this) {
        if (e->fillResult(table, input))
            return true;
    }
    return false;
}

