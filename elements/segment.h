#ifndef __SEGMENT_H__
#define __SEGMENT_H__
#include "set.h"

namespace DP {

class Segment : public Set {
    Point *_beginPoint;
    Point *_endPoint;

public:
    Segment(Plane *parent, Point *a, Point *b);
    Segment(Plane *parent, const char *a, const char *b);
    bool operator == (const Segment &b);
    bool operator != (const Segment &b);
    void addPoint(Point *a);
    Point *getBegin() const;
    Point *getEnd() const;
};

}
#endif /* __SEGMENT_H__ */
