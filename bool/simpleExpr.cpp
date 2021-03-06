#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include "simpleExpr.h"
#include "boolTable.h"
#include "element.h"

using namespace std;
using namespace DP;

DP::SimpleExpr::SimpleExpr(const string &op, const string &descr)
    : BoolExpr(op, descr)
{
}

DP::SimpleExpr::SimpleExpr(const string &op, Element *a, const string &descr)
    : BoolExpr(op, descr)
    , vector(1)
{
    at(0) = a;
}

DP::SimpleExpr::SimpleExpr(const string &op, Element *a, Element *b, const string &descr)
    : BoolExpr(op, descr)
    , vector(2)
{
    at(0) = a;
    at(1) = b;
}

DP::SimpleExpr::SimpleExpr(const string &op, Element *a, Element *b, Element *c, const string &descr)
    : BoolExpr(op, descr)
    , vector(3)
{
    at(0) = a;
    at(1) = b;
    at(2) = c;
}

string DP::SimpleExpr::getString() const
{
    stringstream ss;
    ss << _op << '(';
    vector::const_iterator it = begin();
    if (it != end()) {
        ss << (*it)->getName();

        while (++it != end()) {
            ss << ", " << (*it)->getName();
        }
    }
    ss << ')';
    return ss.str();
}

void SimpleExpr::findArgs(BoolTable &table)
{
    table.addArg(this);
}

bool SimpleExpr::operator==(const SimpleExpr &other)
{
    if (this == &other)
        return true;
    if (getOp() != other.getOp())
        return false;
    if (size() != other.size())
        return false;
    for (uint32_t i = 0; i < size(); i++) {
        if (!(*(at(i)) == *(other[i])))
            return false;
    }
    return true;
}

bool SimpleExpr::fillResult(BoolTable &table, unsigned long int input)
{
    int idx = table.findArgsIndex(this);
    return (1 << idx) & input ? true : false;
}
