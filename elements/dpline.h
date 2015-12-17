#ifndef __DPLINE_H__
#define __DPLINE_H__
#include "dpset.h"

class DPLine : public DPSet {
public:
    DPLine(DPPlan &parent, const char *a, const char *b);
    bool operator == (const DPLine &b);
};

#endif /* __DPLINE_H__ */
