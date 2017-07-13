#include <sstream>
#include <string>
#include "notExpr.h"

using namespace std;

DPNotExpr::DPNotExpr(BoolExpr *a, const string &descr) :
    DPTreeBoolExpr("Not", a, descr == "" ? a->getDescr() : descr)
{

}

bool DPNotExpr::operator() () const
{
    return (!(*at(0))());
}

string DPNotExpr::getString()
{
    stringstream ss;
    ss << "Not " << at(0)->getString();
    return ss.str();
}
