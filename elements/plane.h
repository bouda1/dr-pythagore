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
#ifndef __PLANE_H__
#define __PLANE_H__
#include <deque>
#include <mutex>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include "stack.h"

namespace DP {
class Element;
class Point;
class Line;
class Segment;
class BoolExpr;

class Plane {

    std::unordered_set<Line *> _linesSet;
    std::unordered_set<Segment *> _segmentsSet;
    std::unordered_map<std::string, Point *> _pointsList;

    mutable std::mutex _rulesMutex;
    std::set<std::pair<BoolExpr *, BoolExpr *> > _rules;

    mutable std::mutex _exprsMutex;
    std::set<BoolExpr *> _exprs;

    mutable std::mutex _contradictions_mutex;
    std::deque<std::string> _contradictions;

    Stack _stack;

public:
    Plane();
    Point *getPoint(const char *a) const;
    Line *getLine(Point *a, Point *b);
    Segment *getSegment(Point *a, Point *b);
    void addPoint(Point *a);
    void addLine(Line *a);
    void addSegment(Segment *a);
    bool pointExists(const char *a) const;
    void addExpression(BoolExpr *expr);
    BoolExpr *hasExpr(const std::string &op, Element *a, Element *b) const;
    std::deque<BoolExpr *> getExprs(const std::string &op) const;
    std::deque<BoolExpr *> getExprs(const std::string &op1, const std::string &op2) const;
    void addContradiction(const std::string &err);
    const std::string &getLastContradiction() const;
    void addRule(BoolExpr *e, BoolExpr *f);
};

}

#endif /* __PLANE_H__ */
