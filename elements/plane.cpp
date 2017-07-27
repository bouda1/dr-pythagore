/* Dr-Pythagore
 * Copyright (C) 2016-2017 D. Boucher
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include "plane.h"
#include "point.h"
#include "line.h"
#include "segment.h"
#include "checkequaldistinct.h"
#include "treeBoolExpr.h"
#include "simpleExpr.h"
#include "notBoolExpr.h"
#include "orBoolExpr.h"
#include "boolTable.h"

using namespace std;
using namespace DP;

Plane::Plane()
    : _stack(this)
{
}

deque<BoolExpr *> Plane::getExprs(const string &op) const
{
    deque<BoolExpr *> retval = deque<BoolExpr *>();
    _exprsMutex.lock();
    for (BoolExpr *r : _exprs) {
        if (r->getOp() == op)
            retval.push_back(r);
    }
    _exprsMutex.unlock();
    return retval;
}

deque<BoolExpr *> Plane::getExprs(const string &op1, const string &op2) const
{
    deque<BoolExpr *> retval = deque<BoolExpr *>();
    _exprsMutex.lock();
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
    _exprsMutex.unlock();
    return retval;
}

void Plane::addExpression(BoolExpr *expr)
{
    _exprsMutex.lock();
    _exprs.insert(expr);
    SimpleExpr *simp = dynamic_cast<SimpleExpr *>(expr);
    if (simp && simp->getOp() == "Element") {
        Point *p = static_cast<Point *>(simp->at(0));
        Set *s = static_cast<Set *>(simp->at(1));
        s->addPoint(p);
    }
    _exprsMutex.unlock();

    // FIXME DBR: Add tasks here to involve reasonment
//    if (expr->getOp() == "Distinct" || expr->getOp() == "Equals")
//        _stack.enqueueTask(new CheckEqualDistinct(this));
}

BoolExpr *Plane::hasExpr(const string &op, Element *a, Element *b) const
{
    cout << "hasExpr: " << op << " " << a->getName() << " <=> " << b->getName() << endl;
    BoolExpr *retval = nullptr;
    _exprsMutex.lock();
    for (BoolExpr *expr : _exprs) {
        cout << "  -> Comparing with " << expr->getString() << endl;
        SimpleExpr *simp = dynamic_cast<SimpleExpr *>(expr);
        if (simp) {
            if (expr->getOp() == op) {
                if (simp->at(0) == a && simp->at(1) == b) {
                    retval = expr;
                    cout << "     ...OK" << endl;
                    break;
                }
                else if (simp->at(0) == b && simp->at(1) == a) {
                    retval = expr;
                    cout << "     ...OK" << endl;
                    break;
                }
            }
        }
        else {
            cout << "     Complex..." << endl;
            NotBoolExpr n(expr);
            SimpleExpr s(op, a, b);
            OrBoolExpr res(&n, &s);
            cout << "     " << res.getString() << endl;
            BoolTable table;
            res.findArgs(table);
            res.solve(table);
            if (table.isTrue()) {
                retval = expr;
                break;
            }
        }
    }
    _exprsMutex.unlock();
    return retval;
}

bool Plane::pointExists(const char *a) const
{
    unordered_map<string, Point *>::const_iterator it;
    it = _pointsList.find(a);
    return (it != _pointsList.end());
}

Point *Plane::getPoint(const char *a) const
{
    unordered_map<string, Point *>::const_iterator it;
    it = _pointsList.find(a);
    return (it != _pointsList.end()) ? it->second : nullptr;
}

Line *Plane::getLine(Point *a, Point *b)
{
    Line *retval = nullptr;
    if (*a != *b) {
        for (Line *l : _linesSet) {
            if (l->contains(a, true) && l->contains(b, true))
                return l;
        }

        /* It is not already defined, but we can do it since we have the
         * points and they are distinct */
        retval = new Line(this, a, b);
    }
    return retval;
}

Segment *Plane::getSegment(Point *a, Point *b)
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

void Plane::addPoint(Point *a)
{
    _pointsList[a->getName()] = a;
}

void Plane::addLine(Line *a)
{
    _linesSet.insert(a);
}

void Plane::addSegment(Segment *a)
{
    _segmentsSet.insert(a);
}

void Plane::addContradiction(const string &err)
{
    unique_lock<mutex> lock(_contradictions_mutex);
    _contradictions.push_back(err);
}

/**
 * @brief Plane::getLastContradiction returns the last error stored during
 * computations.
 * @return A reference to this last contradiction string.
 */
const string &Plane::getLastContradiction() const
{
    unique_lock<mutex> lock(_contradictions_mutex);
    const string &retval = _contradictions.back();
    return retval;
}

/**
 * @brief Plane::addRule Add a new rule to the plane. A rule is a pair
 * @containing two expressions E and F param e param f
 */
void Plane::addRule(BoolExpr *e, BoolExpr *f)
{
    _rulesMutex.lock();
    _rules.insert(std::pair<BoolExpr *, BoolExpr *>(e, f));
    _rulesMutex.unlock();
}
