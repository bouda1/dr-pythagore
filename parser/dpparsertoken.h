#ifndef __DPPARSERTOKEN_H__
#define __DPPARSERTOKEN_H__
#include "dpelement.h"
#include "dpplan.h"

class DPParserToken {
    DPPlan &_plan;
    bool _result;
    bool _error;

public:
    DPParserToken(DPPlan &plan);
    void setResult(bool result);
    bool getResult() const;
    void setPlan(DPPlan &plan);
    DPPlan &getPlan() const;
    bool onError() const;
    void setError();
};

#endif /* __DPPARSERTOKEN_H__ */
