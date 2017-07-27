#ifndef __NOT_BOOL_EXPR_H__
#define __NOT_BOOL_EXPR_H__
#include "treeBoolExpr.h"

namespace DP {

class NotBoolExpr : public TreeBoolExpr
{
public:
    NotBoolExpr(BoolExpr *a, const std::string &descr = "");
    virtual bool operator() () const;
    virtual std::string getString() const;
    virtual bool fillResult(BoolTable &table, unsigned long input);
};

}
#endif /* __NOT_BOOL_EXPR_H__ */
