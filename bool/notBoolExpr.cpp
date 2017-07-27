#include <sstream>
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

string NotBoolExpr::getString() const
{
    stringstream ss;
    ss << "Not (" << at(0)->getString() << ')';
    return ss.str();
}

bool NotBoolExpr::fillResult(BoolTable &table, unsigned long input)
{
    return !(at(0)->fillResult(table, input));
}

