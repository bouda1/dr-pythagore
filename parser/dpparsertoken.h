#ifndef __DPPARSERTOKEN_H__
#define __DPPARSERTOKEN_H__
#include "dpelement.h"
#include "dpplan.h"

class DPParserToken {
    DPPlan &_plan;
    DPElement *_el;

public:
    DPParserToken(DPPlan &plan);
    void setElement(DPElement *element);
    DPElement *getElement() const;
    void setPlan(DPPlan &plan);
    DPPlan &getPlan() const;
};

#endif /* __DPPARSERTOKEN_H__ */
