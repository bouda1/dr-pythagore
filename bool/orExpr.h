#ifndef __OR_EXPR_H__
#define __OR_EXPR_H__
#include <vector>
#include "boolBoolExpr.h"

class DPOrExpr : public DPTreeBoolExpr
{
public:
    DPOrExpr(BoolExpr *a, BoolExpr *b, const std::string &descr);
    DPOrExpr(BoolExpr *a, BoolExpr *b, BoolExpr *c, const std::string &descr);
    virtual bool operator() () const;
};

#endif /* __OR_EXPR_H__ */
