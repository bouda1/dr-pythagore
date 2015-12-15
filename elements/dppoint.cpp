#include "dppoint.h"

DPPoint::DPPoint(DPPlan &parent, const char *n)
    : DPElement(parent, n)
{
}

bool DPPoint::operator == (const DPPoint &b)
{
    return getParent().hasRelation(BIN_REL_EQUALS, this, const_cast<DPPoint *>(&b));
}
