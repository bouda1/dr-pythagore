#ifndef __SET_H__
#define __SET_H__
#include <unordered_set>
#include "plan.h"
#include "element.h"

class DPPoint;

class DPSet : public DPElement {
protected:
    std::unordered_set<DPPoint *> _singlePoints;

public:
    bool contains(DPPoint *point) const;
    DPSet(DPPlan *parent);
    void addPoint(DPPoint *a);
    void setRelation(DPBinRel rel, DPElement *a, DPElement *b);
};

#endif /* __SET_H__ */
