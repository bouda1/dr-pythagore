#ifndef __PARSERTOKEN_H__
#define __PARSERTOKEN_H__
#include "element.h"
#include "plan.h"

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

#endif /* __PARSERTOKEN_H__ */
