#ifndef __DPSEGMENT_H__
#define __DPSEGMENT_H__
#include "dpset.h"

class DPSegment : public DPSet {
    DPPoint *_beginPoint;
    DPPoint *_endPoint;

public:
    DPSegment(DPPlan &parent, DPPoint *a, DPPoint *b);
    DPSegment(DPPlan &parent, const char *a, const char *b);
    bool operator == (const DPSegment &b);
    void addPoint(DPPoint *a);
    DPPoint *getBegin() const;
    DPPoint *getEnd() const;
};

#endif /* __DPSEGMENT_H__ */
