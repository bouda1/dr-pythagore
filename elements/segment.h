#ifndef __SEGMENT_H__
#define __SEGMENT_H__
#include "set.h"

class DPSegment : public DPSet {
    DPPoint *_beginPoint;
    DPPoint *_endPoint;

public:
    DPSegment(DPPlan *parent, DPPoint *a, DPPoint *b);
    DPSegment(DPPlan *parent, const char *a, const char *b);
    bool operator == (const DPSegment &b);
    void addPoint(DPPoint *a);
    DPPoint *getBegin() const;
    DPPoint *getEnd() const;
};

#endif /* __SEGMENT_H__ */
