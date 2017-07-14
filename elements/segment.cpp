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
#include <cassert>
#include <sstream>
#include "plane.h"
#include "segment.h"
#include "point.h"
#include "simpleExpr.h"

using namespace std;
using namespace DP;

Segment::Segment(Plane *parent, Point *a, Point *b)
    : Set(parent), _beginPoint(a), _endPoint(b)
{
    stringstream ss;
    ss << '[' << a->getName() << b->getName() << ']';
    setName(ss.str());

    _parent->addSegment(this);
}

Segment::Segment(Plane *parent, const char *a, const char *b)
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
    ss << '[' << a << b << ']';
    setName(ss.str());

    ss << " is a segment";

    /* We must assume points are distinct. */
    SimpleExpr *simp = new SimpleExpr("Distinct", aa, bb, ss.str());
    _parent->addExpression(simp);

    _beginPoint = aa;
    _endPoint = bb;
    _parent->addSegment(this);
}

bool Segment::operator == (const Segment &b)
{
    int count = 0;
    Point *beginPoint = b.getBegin();
    Point *endPoint = b.getEnd();

    return ((*beginPoint == *_beginPoint && *endPoint == *_endPoint)
            || (*beginPoint == *_endPoint && *endPoint == *_beginPoint));
}

bool Segment::operator != (const Segment &b)
{
    int count = 0;
    Point *beginPoint = b.getBegin();
    Point *endPoint = b.getEnd();

    return ((*beginPoint != *_beginPoint && *beginPoint != *_endPoint)
            || (*endPoint != *_beginPoint && *endPoint != *_endPoint));
}

Point *Segment::getEnd() const
{
    return _endPoint;
}

Point *Segment::getBegin() const
{
    return _beginPoint;
}

void Segment::addPoint(Point *a)
{
    if (!_beginPoint)
        _beginPoint = a;
    else if (!_endPoint)
        _endPoint = a;
    else
        assert("This should not arrive" == nullptr);
    Set::addPoint(a);
}
