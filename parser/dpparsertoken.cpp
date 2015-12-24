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

void DPParserToken::setResult(bool result)
{
    _result = result;
}

bool DPParserToken::getResult() const
{
    return _result;
}

bool DPParserToken::onError() const
{
    return _error;
}

void DPParserToken::setError()
{
    _error = true;
}
