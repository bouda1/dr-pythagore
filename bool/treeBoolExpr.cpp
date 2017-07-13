#include <vector>
#include "treeBoolExpr.h"

using namespace std;
using namespace DP;

TreeBoolExpr::TreeBoolExpr(const string &op, BoolExpr *a, const string &descr) :
    BoolExpr(op, descr != "" ? descr : a->getDescr()), vector(1)
{
    at(0) = a;
}

TreeBoolExpr::TreeBoolExpr(const string &op, BoolExpr *a, BoolExpr *b, const string &descr) :
    BoolExpr(op, descr), vector(2)
{
    at(0) = a;
    at(1) = b;
}

TreeBoolExpr::TreeBoolExpr(const string &op, BoolExpr *a, BoolExpr *b, BoolExpr *c, const string &descr) :
    BoolExpr(op, descr), vector(3)
{
    at(0) = a;
    at(1) = b;
    at(2) = c;
}

string TreeBoolExpr::getString()
{
    return string("FIXME TREE_BOOL_EXPR NOT IMPLEMENTED");
}

bool TreeBoolExpr::operator()() const
{
    return !(*at(0))();
}
