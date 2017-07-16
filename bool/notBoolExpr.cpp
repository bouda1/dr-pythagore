#include <iostream>
#include "notBoolExpr.h"

using namespace std;
using namespace DP;

NotBoolExpr::NotBoolExpr(BoolExpr *a, const string &descr)
    : TreeBoolExpr("Not", a, descr)
{
}

bool NotBoolExpr::operator()() const
{
    return !(*at(0))();
}

string NotBoolExpr::getString()
{
    cout << "Not (" << at(0)->getString() << ')';
}

bool NotBoolExpr::fillResult(BoolTable &table, unsigned long input)
{
    return !(at(0)->fillResult(table, input));
}

