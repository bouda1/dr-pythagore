#include "dpset.h"

using namespace std;

DPSet::DPSet(DPPlan &parent)
    : DPElement(parent)
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
