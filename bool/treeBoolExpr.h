#ifndef __TREE_BOOL_EXPR_H__
#define __TREE_BOOL_EXPR_H__
#include <string>
#include <vector>
#include "boolExpr.h"

namespace DP {

class TreeBoolExpr : public BoolExpr, public std::vector<BoolExpr *>
{
public:
    TreeBoolExpr(const std::string &op, BoolExpr *a, const std::string &descr = "");
    TreeBoolExpr(const std::string &op, BoolExpr *a, BoolExpr *b, const std::string &descr = "");
    TreeBoolExpr(const std::string &op, BoolExpr *a, BoolExpr *b, BoolExpr *c, const std::string &descr);
    static TreeBoolExpr Not(BoolExpr *a, const std::string &descr = "");
    virtual std::string getString();
    virtual bool operator() () const;
};

inline TreeBoolExpr TreeBoolExpr::Not(BoolExpr *a, const std::string &descr)
{
    return TreeBoolExpr("Not", a, descr != "" ? descr : a->getDescr());
}

}

#endif /* __TREE_BOOL_EXPR_H__ */
