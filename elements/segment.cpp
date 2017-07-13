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
