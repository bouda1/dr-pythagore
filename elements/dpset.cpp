#include "dpset.h"

using namespace std;

DPSet::DPSet(DPPlan &parent)
    : DPElement(parent)
    , m_single_points()
{
}

bool DPSet::contains(const DPPoint &point)
{
    return false;
}

bool DPSet::contains(const DPSet &point)
{
    return false;
}

void DPSet::addPoint(DPPoint *a)
{
    m_single_points.push_back(a);
}
