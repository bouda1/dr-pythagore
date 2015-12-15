#ifndef __DPSET_H__
#define __DPSET_H__
#include <list>
#include "dpplan.h"
#include "dpelement.h"

class DPPoint;

class DPSet : public DPElement {
    std::list<DPPoint *> m_single_points;

public:
    bool contains(const DPPoint &point);
    bool contains(const DPSet &set);
    DPSet(DPPlan &parent);
    void addPoint(DPPoint *a);
    void setRelation(DPBinRel rel, DPElement *a, DPElement *b);
};

#endif /* __DPSET_H__ */
