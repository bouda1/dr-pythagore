#include "dppoint.h"

DPPoint::DPPoint(DPPlan &parent, const char *n)
    : DPElement(parent, n)
{
    getParent().addPoint(this);
}

bool DPPoint::operator == (const DPPoint &b)
{
    if (this == &b)
        return true;
    return getParent().hasRelation(BIN_REL_EQUALS, this, const_cast<DPPoint *>(&b));
}

bool DPPoint::operator == (const DPPoint &b)
{
    return getParent().hasRelation(BIN_REL_EQUALS, this, const_cast<DPPoint *>(&b));
}
