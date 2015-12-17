#include "dpset.h"

using namespace std;

DPSet::DPSet(DPPlan &parent)
    : DPElement(parent)
    , _single_points()
{
}

bool DPSet::contains(DPPoint *point)
{
    unordered_set<DPPoint *>::iterator it = _single_points.find(point);

    return it != _single_points.end();
}

bool DPSet::contains(const DPSet &point)
{
    return false;
}

void DPSet::addPoint(DPPoint *a)
{
    _single_points.insert(a);
}
