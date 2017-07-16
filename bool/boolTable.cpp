#include <cassert>
#include <bitset>
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

void BoolTable::clearArgs()
{
    _args.clear();
}

size_t BoolTable::countArgs() const
{
    return _args.size();
}

string BoolTable::getString()
{
    stringstream ss;
    for (SimpleExpr *e : _args)
        ss << e->getString() << " ; ";
    ss << "\n\n";
    for (unsigned int i = 0; i < _result.size(); ++i) {
        unsigned int nb = i;
        for (unsigned int k = 0; k < _args.size(); ++k) {
            if (nb & 1)
                ss << " 1";
            else
                ss << " 0";
            nb = nb >> 1;
        }

        ss << " : " << _result[i] << '\n';
    }
    ss << '\n';
    return ss.str();
}

size_t BoolTable::findArgsIndex(BoolExpr *expr)
{
    size_t i;
    for (i = 0; i < _args.size(); i++) {
        if (expr == _args[i])
            return i;
    }
    assert(1 == 0);
    return 0;  // Should not arrive
}

void BoolTable::setResult(std::vector<bool> &result)
{
    _result = result;
}
