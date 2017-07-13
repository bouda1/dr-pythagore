#ifndef __NOT_EXPR_H__
#define __NOT_EXPR_H__
#include "treeBoolExpr.h"

namespace DP {
class DPNotExpr : public DPTreeBoolExpr
{
public:
    DPNotExpr(BoolExpr *a, const std::string &descr = "");
    virtual bool operator() () const;
    virtual std::string getString();
};
}
#endif /* __NOT_EXPR_H__ */
