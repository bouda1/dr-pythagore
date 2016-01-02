#include <sstream>
#include "plan.h"
#include "line.h"
#include "point.h"

using namespace std;

DPLine::DPLine(DPPlan *parent, DPPoint *a, DPPoint *b)
    : DPSet(parent)
{
    stringstream ss;
    ss << '(' << a->getName() << b->getName() << ')';
    setName(ss.str());

    addPoint(a);
    addPoint(b);
    _parent->addLine(this);
}

DPLine::DPLine(DPPlan *parent, const char *a, const char *b)
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

    /* We must assume points are distinct. */
    _parent->setRelation(BIN_REL_DISTINCT, aa, bb);

    addPoint(aa);
    addPoint(bb);
    _parent->addLine(this);
}

bool DPLine::operator == (const DPLine &b)
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
