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
    std::vector<bool> _result;

public:
    BoolTable();
    void addArg(SimpleExpr *expr);
    void clearArgs();
    size_t countArgs() const;
    std::list<std::vector<bool> > &getArray();
    std::string getString();
    size_t findArgsIndex(SimpleExpr *expr);
    void setResult(std::vector<bool> &result);
    bool isTrue() const;
};
}
#endif /* __BOOL_TABLE_H__ */
