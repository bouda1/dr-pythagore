#ifndef __DPSET_H__
#define __DPSET_H__
#include "dpelement.h"
#include "dppoint.h"

class DPSet : public DPElement
{
    public:
        bool contains(const DPPoint &point);
        bool contains(const DPSet &set);
        DPSet(DPPlan &parent);
};

#endif /* __DPSET_H__ */
