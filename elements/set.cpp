#include "set.h"

using namespace std;
using namespace DP;

Set::Set(Plane *parent)
    : Element(parent)
    , _singlePoints()
{
}

bool Set::contains(Point *point) const
{
    unique_lock<mutex> lock(_singlePointsMutex);
    unordered_set<Point *>::const_iterator it = _singlePoints.find(point);

    return it != _singlePoints.end();
}

void Set::addPoint(Point *a)
{
    unique_lock<mutex> lock(_singlePointsMutex);
    _singlePoints.insert(a);
}

unordered_set<Point *> Set::getSinglePoints() const
{
    unique_lock<mutex> lock(_singlePointsMutex);
    return _singlePoints;
}
