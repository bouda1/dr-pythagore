#include <iostream>
#include "point.h"

using namespace std;

DPPoint::DPPoint(DPPlane *parent, const char *n)
    : DPElement(parent, n)
{
    cout << "\x1b[33;1m" << "New point " << n << "\x1b[0m" << endl;
    parent->addPoint(this);
}

bool DPPoint::operator == (const DPPoint &b)
{
    if (this == &b)
        return true;
    return getParent()->hasRelation(OP_REL_EQUALS, this,
                                   const_cast<DPPoint *>(&b));
}

bool DPPoint::operator != (const DPPoint &b)
{
    if (this == &b)
        return false;
    return getParent()->hasRelation(OP_REL_DISTINCT, this,
                                    const_cast<DPPoint *>(&b));
}
