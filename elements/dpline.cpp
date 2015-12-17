#include <sstream>
#include "dpplan.h"
#include "dpline.h"
#include "dppoint.h"

using namespace std;

DPLine::DPLine(DPPlan &parent, const char *a, const char *b)
    : DPSet(parent)

{
    DPPoint *aa, *bb;

    if (parent.pointExists(a))
        aa = parent.getPoint(a);
    else
        aa = new DPPoint(parent, a);

    if (parent.pointExists(b))
        bb = parent.getPoint(b);
    else
        bb = new DPPoint(parent, b);

    stringstream ss;
    ss << '(' << aa->getName() << bb->getName() << ')';
    setName(ss.str());

    /* We must assume points are distinct. */
    parent.setRelation(BIN_REL_DISTINCT, aa, bb);

    addPoint(aa);
    addPoint(bb);
    parent.addLine(this);
}

bool DPLine::operator == (const DPLine &b)
{
    int count = 0;
    DPPoint *first_point = nullptr;

    for (DPPoint *p : _singlePoints) {
        if (count == 0 && const_cast<DPLine&>(b).contains(p)) {
            count++;
            first_point = p;
        }
        else if (count > 0 && *p != *first_point
                 && const_cast<DPLine &>(b).contains(p))
            return true;
    }
    return false;
}
