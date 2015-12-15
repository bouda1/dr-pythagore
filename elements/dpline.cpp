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

    /* We must assume points are distinct. */
    parent.setRelation(BIN_REL_DISTINCT, aa, bb);

    addPoint(aa);
    addPoint(bb);
}
