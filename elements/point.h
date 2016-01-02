#ifndef __POINT_H__
#define __POINT_H__
#include "element.h"

class DPPoint : public DPElement
{
    public:
        DPPoint(DPPlan *parent, const char *name);
        bool operator == (const DPPoint &b);
        bool operator != (const DPPoint &b);
};

#endif /* __POINT_H__ */
