#include "set.h"

using namespace std;

DPSet::DPSet(DPPlane *parent)
    : DPElement(parent)
    , _singlePoints()
{
}

bool DPSet::contains(DPPoint *point) const
{
    unique_lock<mutex> lock(_singlePointsMutex);
    unordered_set<DPPoint *>::const_iterator it = _singlePoints.find(point);

    return it != _singlePoints.end();
}

void DPSet::addPoint(DPPoint *a)
{
    unique_lock<mutex> lock(_singlePointsMutex);
    _singlePoints.insert(a);
}

unordered_set<DPPoint *> DPSet::getSinglePoints() const
{
    unique_lock<mutex> lock(_singlePointsMutex);
    return _singlePoints;
}
