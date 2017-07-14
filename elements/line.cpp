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
#include <sstream>
#include "plane.h"
#include "line.h"
#include "point.h"
#include "simpleExpr.h"

using namespace std;
using namespace DP;

/**
 * @brief Line::Line Constructor
 * @param parent The plane containing this line
 * @param a A point contained by the line
 * @param b A second point contained by the line
 * When a line is constructed from two points, it is automatically assumed
 * those two points to be distinct.
 */
Line::Line(Plane *parent, Point *a, Point *b)
    : Set(parent)
{
    stringstream ss;
    ss << '(' << a->getName() << b->getName() << ')';
    setName(ss.str());

    ss << " is a line";

    /* We must assume points are distinct */
    SimpleExpr *expr = new SimpleExpr("Distinct", a, b, ss.str());
    _parent->addExpression(expr);

    addPoint(a);
    addPoint(b);
    _parent->addLine(this);
}

/**
 * @brief Line::Line Constructor
 * @param parent The plane containing the line
 * @param a A point name
 * @param b A second point name
 * The line is the one passing by a and b. Those two points are supposed to be
 * distinct.
 */
Line::Line(Plane *parent, const char *a, const char *b)
    : Set(parent)
{
    Point *aa, *bb;

    if (_parent->pointExists(a))
        aa = _parent->getPoint(a);
    else
        aa = new Point(parent, a);

    if (_parent->pointExists(b))
        bb = _parent->getPoint(b);
    else
        bb = new Point(parent, b);

    stringstream ss;
    ss << '(' << a << b << ')';
    setName(ss.str());

    ss << " is a line";

    /* We must assume points are distinct. */
    SimpleExpr *simp = new SimpleExpr("Distinct", aa, bb, ss.str());
    _parent->addExpression(simp);

    addPoint(aa);
    addPoint(bb);
    _parent->addLine(this);
}

/**
 * @brief Line::operator == Surcharged to compare two lines
 * @param b
 * @return A boolean telling if the compared lines are the same or not.
 */
bool Line::operator == (const Line &b) const
{
    int count = 0;
    Point *first_point = nullptr;

    for (Point *p : _singlePoints) {
        if (count == 0 && b.contains(p)) {
            count++;
            first_point = p;
        }
        else if (count > 0 && *p != *first_point && b.contains(p))
            return true;
    }
    return false;
}

/**
 * @brief Line::parallelTo Check if the lines are parallel
 * @param b Another line to compare with.
 * @return A boolean telling if the lines are parallel
 */
bool Line::parallelTo(const Line &b) const
{
    return getParent()->hasExpr("Parallel", const_cast<Line *>(this), const_cast<Line *>(&b));
}
