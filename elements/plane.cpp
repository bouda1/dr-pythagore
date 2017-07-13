#include <iostream>
#include "plane.h"
#include "point.h"
#include "line.h"
#include "segment.h"
#include "checkequaldistinct.h"
#include "treeBoolExpr.h"
#include "simpleExpr.h"

using namespace std;
using namespace DP;

DP::Plane::Plane()
    : _stack(this)
{}

std::deque<BoolExpr *> DP::Plane::getExprs(const string &op) const
{
    unique_lock<mutex> lock(_exprsMutex);
    deque<BoolExpr *> retval = deque<BoolExpr *>();
    for (BoolExpr *r : _exprs) {
        if (r->getOp() == op)
            retval.push_back(r);
    }
    return retval;
}

std::deque<BoolExpr *> DP::Plane::getExprs(const string &op1, const string &op2) const
{
    unique_lock<mutex> lock(_exprsMutex);
    deque<BoolExpr *> retval = deque<BoolExpr *>();
    for (BoolExpr *r : _exprs) {
        if (r->getOp() == op1) {
            TreeBoolExpr *tree = dynamic_cast<TreeBoolExpr *>(r);
            if (tree) {
                for (BoolExpr *e : *tree) {
                    if (e->getOp() == op2) {
                        retval.push_back(r);
                        break;
                    }
                }
            }
        }
    }
    return retval;
}

void DP::Plane::addExpression(BoolExpr *expr)
{
    _exprsMutex.lock();
    _exprs.insert(expr);
    _exprsMutex.unlock();

    if (expr->getOp() == "Distinct" || expr->getOp() == "Equals")
        _stack.enqueueTask(new CheckEqualDistinct(this));

}

//void DP::Plane::setRelation(DPOpRel op, Element *a, Element *b, const string &explanation)
//{
//    _rulesMutex.lock();
//    Rule *rule = new Rule(op, a, b, explanation);
//    _rules.insert(rule);
//    _rulesMutex.unlock();

//    _stack.enqueueTask(new TaskRule(this, rule));
//    if (op == OP_REL_DISTINCT || op == OP_REL_EQUALS)
//        _stack.enqueueTask(new CheckEqualDistinct(this));
//    else if (op == OP_REL_ALIGNED)
//        _stack.enqueueTask(new DPTaskLua(this, "check_aligned.lua"));
//}

//void DP::Plane::setRelation(DPOpRel op, Element *a, Element *b, Element *c, const string &explanation)
//{
//    _rulesMutex.lock();
//    Rule *rule = new Rule(op, a, b, c, explanation);
//    _rules.insert(rule);
//    _rulesMutex.unlock();

//    _stack.enqueueTask(new TaskRule(this, rule));
//}

BoolExpr *DP::Plane::hasExpr(const string &op, Element *a, Element *b) const
{
    {
        unique_lock<mutex> lock(_exprsMutex);
        for (BoolExpr *expr: _exprs) {
            //FIXME: Not finished
            if (expr->getOp() == op) {
                SimpleExpr *simp = dynamic_cast<SimpleExpr *>(expr);
                if (simp) {
                    if (simp->at(0) == a && simp->at(1) == b)
                        return expr;
                    else if (simp->at(0) == b && simp->at(1) == a)
                        return expr;
                }
            }
        }
    }
    return nullptr;
}

//Rule *DP::Plane::hasRelation(DPOpRel op, Element *a, Element *b) const
//{
//    {
//        unique_lock<mutex> lock(_rulesMutex);
//        for (Rule *rule : _rules) {
//            if (rule->getOp() == op) {
//                if (rule->get(0) == a && rule->get(1) == b)
//                    return rule;
//                else if (rule->get(0) == b && rule->get(1) == a)
//                    return rule;
//            }
//        }
//    }
//    return nullptr;
//}

bool DP::Plane::pointExists(const char *a) const
{
    unordered_map<string, Point *>::const_iterator it;
    it = _pointsList.find(a);
    return (it != _pointsList.end());
}

Point *DP::Plane::getPoint(const char *a) const
{
    unordered_map<string, Point *>::const_iterator it;
    it = _pointsList.find(a);
    return (it != _pointsList.end()) ? it->second : nullptr;
}

Line *DP::Plane::getLine(Point *a, Point *b)
{
    Line *retval = nullptr;
    if (*a != *b) {
        for (Line *l : _linesSet) {
            if (l->contains(a) && l->contains(b))
                return l;
        }

        /* It is not already defined, but we can do it since we have the
         * points and they are distinct */
        retval = new Line(this, a, b);
    }
    return retval;
}

Segment *DP::Plane::getSegment(Point *a, Point *b)
{
    Segment *retval = nullptr;
    if (*a != *b) {
        for (Segment *s : _segmentsSet) {
            Point *begin = s->getBegin();
            Point *end = s->getEnd();
            if ((*begin == *a && *end == *b)
                || (*begin == *b && *end == *a))
                return s;
        }

        /* It is not already defined, but we can do it since we have the
         * points and they are distinct */
        retval = new Segment(this, a, b);
    }
    return retval;
}

void DP::Plane::addPoint(Point *a)
{
    _pointsList[a->getName()] = a;
}

void DP::Plane::addLine(Line *a)
{
    _linesSet.insert(a);
}

void DP::Plane::addSegment(Segment *a)
{
    _segmentsSet.insert(a);
}

void DP::Plane::addContradiction(const string &err)
{
    unique_lock<mutex> lock(_contradictions_mutex);
    _contradictions.push_back(err);
}

string DP::Plane::getLastContradiction() const
{
    unique_lock<mutex> lock(_contradictions_mutex);
    string retval = _contradictions.back();
    return retval;
}

