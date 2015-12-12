#include "dpparsertoken.h"

DPParserToken::DPParserToken(DPPlan &plan)
    : _plan(plan)
{
}

void DPParserToken::setPlan(DPPlan &plan)
{
    _plan = plan;
}

DPPlan &DPParserToken::getPlan() const
{
    return _plan;
}

void DPParserToken::setElement(DPElement *element)
{
    _el = element;
}

DPElement *DPParserToken::getElement() const
{
    return _el;
}
