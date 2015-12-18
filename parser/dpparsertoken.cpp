#include "dpparsertoken.h"

DPParserToken::DPParserToken(DPPlan &plan)
    : _plan(plan), _error(false)
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

bool DPParserToken::onError() const
{
    return _error;
}

void DPParserToken::setError()
{
    _error = true;
}
