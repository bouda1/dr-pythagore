#include <sstream>
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
    cout << "Evaluation of And..." << endl;
    cout << "Table: " << getString() << endl;
    for (BoolExpr *e : *this) {
        if (!(*e)())
            return false;
    }
    return true;
}

string AndBoolExpr::getString() const
{
    stringstream ss;
    ss << '(' << at(0)->getString() << ") And (" << at(1)->getString() << ')';
    return ss.str();
}

bool AndBoolExpr::fillResult(BoolTable &table, unsigned long input)
{
    for (BoolExpr *e : *this) {
        if (!e->fillResult(table, input))
            return false;
    }
    return true;
}
