#include "parsertoken.h"

using namespace DP;

ParserToken::ParserToken(const Plane *plan)
    : _plane(plan)
    , _error(false)
{
}

Plane *ParserToken::getPlane() const
{
    return const_cast<Plane *>(_plane);
}

void ParserToken::setResult(bool result)
{
    _result = result;
}

bool ParserToken::getResult() const
{
    return _result;
}

bool ParserToken::onError() const
{
    return _error;
}

void ParserToken::setError(bool err)
{
    _error = err;
}
