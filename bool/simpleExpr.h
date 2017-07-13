#ifndef _SIMPLE_EXPR_H_
#define _SIMPLE_EXPR_H_
#include "boolExpr.h"
#include <vector>

namespace DP
{

class Element;

class SimpleExpr : public BoolExpr, public std::vector<Element *>
{
public:
    SimpleExpr(const std::string &op, const std::string &descr);
    SimpleExpr(const std::string &op, Element *a, const std::string &descr);
    SimpleExpr(const std::string &op, Element *a, Element *b, const std::string &descr);
    SimpleExpr(const std::string &op, Element *a, Element *b, Element *c, const std::string &descr);

    virtual std::string getString();
};

}
#endif // _SIMPLE_EXPR_H_
