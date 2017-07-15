#ifndef __BOOL_TABLE_H__
#define __BOOL_TABLE_H__
#include <vector>
#include <list>
#include <deque>
#include <string>

namespace DP {
class BoolExpr;
class SimpleExpr;

class BoolTable
{
    std::deque<SimpleExpr *> _args;
    std::list<std::vector<bool> > _array;

public:
    BoolTable();
    void addArg(SimpleExpr *expr);
    std::list<std::vector<bool> > &getArray();
    std::string getString();
};
}
#endif /* __BOOL_TABLE_H__ */
