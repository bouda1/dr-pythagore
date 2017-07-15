#include <sstream>
#include "boolTable.h"
#include "boolExpr.h"
#include "simpleExpr.h"

using namespace std;
using namespace DP;

BoolTable::BoolTable()
{
}

void BoolTable::addArg(SimpleExpr *expr)
{
    _args.push_back(expr);
}

list<vector<bool> > &BoolTable::getArray()
{
    return _array;
}

string BoolTable::getString()
{
    stringstream ss;
    for (SimpleExpr *e : _args)
        ss << e->getString() << " ; ";
    ss << "\n\n";
    for (vector<bool> &v : _array) {
        for (bool b : v) {
            ss << ' ' << (b ? '1' : '0');
        }
        ss << '\n';
    }
    return ss.str();
}
