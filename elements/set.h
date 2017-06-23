#ifndef __SET_H__
#define __SET_H__
#include <unordered_set>
#include <mutex>
#include "plane.h"
#include "element.h"

class DPPoint;

class DPSet : public DPElement {
protected:
    std::unordered_set<DPPoint *> _singlePoints;
    mutable std::mutex _singlePointsMutex;

public:
    bool contains(DPPoint *point) const;
    DPSet(DPPlane *parent);
    void addPoint(DPPoint *a);
    std::unordered_set<DPPoint *> getSinglePoints() const;
    void setRelation(DPOpRel rel, DPElement *a, DPElement *b);
};

#endif /* __SET_H__ */
