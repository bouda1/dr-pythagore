#include "set.h"

using namespace std;

DPSet::DPSet(DPPlan *parent)
    : DPElement(parent)
    , _singlePoints()
{
}

bool DPSet::contains(DPPoint *point) const
{
    unordered_set<DPPoint *>::const_iterator it = _singlePoints.find(point);

    return it != _singlePoints.end();
}

void DPSet::addPoint(DPPoint *a)
{
    _singlePoints.insert(a);
}
