#ifndef __AND_EXPR_H__
#define __AND_EXPR_H__
#include <vector>
#include "treeBoolExpr.h"

class DPAndExpr : public TreeBoolExpr
{
public:
    DPAndExpr(BoolExpr *a, BoolExpr *b, const std::string &descr);
    DPAndExpr(BoolExpr *a, BoolExpr *b, BoolExpr *c, const std::string &descr);
    virtual bool operator() () const;
};

#endif /* __AND_EXPR_H__ */
