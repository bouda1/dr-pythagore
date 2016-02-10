#include <cassert>
#include <sstream>
#include "plan.h"
#include "segment.h"
#include "point.h"

using namespace std;

DPSegment::DPSegment(DPPlan *parent, DPPoint *a, DPPoint *b)
    : DPSet(parent), _beginPoint(a), _endPoint(b)
{
    stringstream ss;
    ss << '[' << a->getName() << b->getName() << ']';
    setName(ss.str());

    _parent->addSegment(this);
}

DPSegment::DPSegment(DPPlan *parent, const char *a, const char *b)
    : DPSet(parent)

{
    DPPoint *aa, *bb;

    if (_parent->pointExists(a))
        aa = _parent->getPoint(a);
    else
        aa = new DPPoint(parent, a);

    if (_parent->pointExists(b))
        bb = _parent->getPoint(b);
    else
        bb = new DPPoint(parent, b);

    stringstream ss;
    ss << '[' << a << b << ']';
    setName(ss.str());

    ss << " is a segment";

    /* We must assume points are distinct. */
    _parent->setRelation(BIN_REL_DISTINCT, aa, bb, ss.str());

    _beginPoint = aa;
    _endPoint = bb;
    _parent->addSegment(this);
}

bool DPSegment::operator == (const DPSegment &b)
{
    int count = 0;
    DPPoint *beginPoint = b.getBegin();
    DPPoint *endPoint = b.getEnd();

    return ((*beginPoint == *_beginPoint && *endPoint == *_endPoint)
            || (*beginPoint == *_endPoint && *endPoint == *_beginPoint));
}

bool DPSegment::operator != (const DPSegment &b)
{
    int count = 0;
    DPPoint *beginPoint = b.getBegin();
    DPPoint *endPoint = b.getEnd();

    return ((*beginPoint != *_beginPoint && *beginPoint != *_endPoint)
            || (*endPoint != *_beginPoint && *endPoint != *_endPoint));
}

DPPoint *DPSegment::getEnd() const
{
    return _endPoint;
}

DPPoint *DPSegment::getBegin() const
{
    return _beginPoint;
}

void DPSegment::addPoint(DPPoint *a)
{
    if (!_beginPoint)
        _beginPoint = a;
    else if (!_endPoint)
        _endPoint = a;
    else
        assert("This should not arrive" == nullptr);
    DPSet::addPoint(a);
}
