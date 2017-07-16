#include <vector>
#include "boolExpr.h"
#include "boolTable.h"

using namespace std;
using namespace DP;

/**
 * @brief BoolExpr::BoolExpr Constructor
 * @param op An operator name
 * @param descr A description
 */
BoolExpr::BoolExpr(const string &op, const string &descr) :
    _op(op), _descr(descr)
{
}

/**
 * @brief BoolExpr::operator () Evaluates the expression
 *
 * By default, the returned value is true.
 *
 * @return a boolean
 */
bool BoolExpr::operator()() const
{
    return true;    
}

/**
 * @brief BoolExpr::getDescr returns a reference to the description
 * @return A string reference
 */
const string &BoolExpr::getDescr() const
{
    return _descr;
}

/**
 * @brief BoolExpr::getOp returns a reference to the operator name
 * @return A string reference
 */
const string &BoolExpr::getOp() const
{
    return _op;
}

/**
 * @brief BoolExpr::solve Fills a Karnaugh table from the current boolean
 * equation.
 * @param table The table to fill.
 *
 * FIXME: Maybe this function could return the table instead of needing it
 * in parameter.
 */
void BoolExpr::solve(BoolTable &table)
{
    /* FIXME I don't like the idea to fill table from BoolExpr.
     * Maybe the reverse would be better... */
    table.clearArgs();
    findArgs(table);
    unsigned long int size = 1 << table.countArgs();
    vector<bool> retval(size);
    for (unsigned long int i = 0; i < size; ++i) {
        retval[i] = fillResult(table, i);
    }
    table.setResult(retval);
}
