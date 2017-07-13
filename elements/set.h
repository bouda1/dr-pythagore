#ifndef __SET_H__
#define __SET_H__
#include <unordered_set>
#include <mutex>
#include "plane.h"
#include "element.h"

namespace DP {

class Point;

class Set : public Element {
protected:
    std::unordered_set<Point *> _singlePoints;
    mutable std::mutex _singlePointsMutex;

public:
    bool contains(Point *point) const;
    Set(Plane *parent);
    void addPoint(Point *a);
    std::unordered_set<Point *> getSinglePoints() const;
    //void setRelation(DPOpRel rel, Element *a, Element *b);
};

}

#endif /* __SET_H__ */
