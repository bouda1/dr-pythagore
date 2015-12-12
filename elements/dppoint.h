#ifndef __DPPOINT_H__
#define __DPPOINT_H__
#include "dpelement.h"

class DPPoint : public DPElement
{
    public:
        DPPoint(DPPlan &parent, const char *name);
};

#endif /* __DPPOINT_H__ */
