#include "boolExpr.h"
#include "boolTable.h"

using namespace std;
using namespace DP;

BoolExpr::BoolExpr(const string &op, const string &descr) :
    _op(op), _descr(descr)
{
}

bool BoolExpr::operator()() const
{
    return true;    
}

const string &BoolExpr::getDescr() const
{
    return _descr;
}

const string &BoolExpr::getOp() const
{
    return _op;
}
