#ifndef __BOOL_EXPR_H__
#define __BOOL_EXPR_H__
#include <string>
#include <deque>

namespace DP {

class Element;
class BoolTable;
class SimpleExpr;

class BoolExpr
{
protected:
    std::string _op;
    std::string _descr;

public:
    BoolExpr(const std::string &op, const std::string &descr);
    virtual bool operator() () const;
    virtual std::string getString() = 0;
    const std::string &getDescr() const;
    const std::string &getOp() const;
    virtual void solve(BoolTable &table) = 0;
};

}

#endif /* __BOOL_EXPR_H__ */