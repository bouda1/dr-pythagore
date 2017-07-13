#include "parsertoken.h"

using namespace DP;

ParserToken::ParserToken(const Plane *plan)
    : _plan(plan), _error(false)
{
}

Plane *ParserToken::getPlan() const
{
    return const_cast<Plane *>(_plan);
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

void ParserToken::setError()
{
    _error = true;
}
