#ifndef __ASSOC_H__
#define __ASSOC_H__
#include "plan.h"

enum DPType {
    DP_TYPE_POINT,
    DP_TYPE_LINE,
    DP_TYPE_SEGMENT,
    DP_TYPE_COUNT
};

class DPAssoc {
    DPBinRel _op;
    DPType _type;
    DPElement *_el1;
    DPElement *_el2;

public:
    DPAssoc(DPBinRel op, DPType type, DPElement *el1, DPElement *el2);
};

#endif /* __ASSOC_H__ */
