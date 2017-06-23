#include <sstream>
#include "plane.h"
#include "line.h"
#include "point.h"

using namespace std;

DPLine::DPLine(DPPlane *parent, DPPoint *a, DPPoint *b)
    : DPSet(parent)
{
    stringstream ss;
    ss << '(' << a->getName() << b->getName() << ')';
    setName(ss.str());

    ss << " is a line";

    /* We must assume points are distinct */
    _parent->setRelation(OP_REL_DISTINCT, a, b, ss.str());

    addPoint(a);
    addPoint(b);
    _parent->addLine(this);
}

DPLine::DPLine(DPPlane *parent, const char *a, const char *b)
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
    ss << '(' << a << b << ')';
    setName(ss.str());

    ss << " is a line";

    /* We must assume points are distinct. */
    _parent->setRelation(OP_REL_DISTINCT, aa, bb, ss.str());

    addPoint(aa);
    addPoint(bb);
    _parent->addLine(this);
}

bool DPLine::operator == (const DPLine &b) const
{
    int count = 0;
    DPPoint *first_point = nullptr;

    for (DPPoint *p : _singlePoints) {
        if (count == 0 && b.contains(p)) {
            count++;
            first_point = p;
        }
        else if (count > 0 && *p != *first_point && b.contains(p))
            return true;
    }
    return false;
}

bool DPLine::parallelTo(const DPLine &b) const
{
    return getParent()->hasRelation(OP_REL_PARALLEL,
                                    const_cast<DPLine *>(this), const_cast<DPLine *>(&b));
}
