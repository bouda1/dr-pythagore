#include "parsertoken.h"

DPParserToken::DPParserToken(const DPPlane *plan)
    : _plan(plan), _error(false)
{
}

DPPlane *DPParserToken::getPlan() const
{
    return const_cast<DPPlane *>(_plan);
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
