#include "set.h"

using namespace std;

DPSet::DPSet(DPPlan &parent)
    : DPElement(parent)
    , _singlePoints()
{
}

bool DPSet::contains(DPPoint *point)
{
    unordered_set<DPPoint *>::iterator it = _singlePoints.find(point);

    return it != _singlePoints.end();
}

void DPSet::addPoint(DPPoint *a)
{
    _singlePoints.insert(a);
}
