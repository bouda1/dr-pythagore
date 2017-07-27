#ifndef __OR_BOOL_EXPR_H__
#define __OR_BOOL_EXPR_H__
#include <deque>
#include "treeBoolExpr.h"

namespace DP {
class OrBoolExpr : public TreeBoolExpr
{
protected:

public:
    OrBoolExpr(BoolExpr *a, BoolExpr *b, const std::string &descr = "");
    virtual bool operator() () const;
    virtual std::string getString() const;
    virtual bool fillResult(BoolTable &table, unsigned long int input);
};
}
#endif /* __OR_BOOL_EXPR_H__ */
