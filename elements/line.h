#ifndef __LINE_H__
#define __LINE_H__
#include "set.h"

class DPLine : public DPSet {
public:
    DPLine(DPPlan *parent, DPPoint *a, DPPoint *b);
    DPLine(DPPlan *parent, const char *a, const char *b);
    bool operator == (const DPLine &b) const;
    bool parallelTo(const DPLine &b) const;
};

#endif /* __LINE_H__ */
