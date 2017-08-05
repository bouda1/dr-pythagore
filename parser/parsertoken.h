#ifndef __PARSERTOKEN_H__
#define __PARSERTOKEN_H__
#include "element.h"
#include "plane.h"

namespace DP {
class ParserToken
{
    const Plane *_plane;
    bool _result;
    bool _error;

public:
    ParserToken(const Plane *plan);
    void setResult(bool result);
    bool getResult() const;
    Plane *getPlane() const;
    bool onError() const;
    void setError(bool err);
};
}

#endif /* __PARSERTOKEN_H__ */
