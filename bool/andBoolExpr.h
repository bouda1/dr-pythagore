#ifndef __ANDBOOLEXPR_H__
#define __ANDBOOLEXPR_H__
#include "treeBoolExpr.h"

namespace DP {
class AndBoolExpr : public TreeBoolExpr
{
public:
    AndBoolExpr(BoolExpr *a, BoolExpr *b, const std::string &descr = "");
    virtual bool operator() () const;
    virtual std::string getString();
    virtual bool fillResult(BoolTable &table, unsigned long input);
};
}
#endif // __ANDBOOLEXPR_H__
