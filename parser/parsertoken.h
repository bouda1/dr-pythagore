#ifndef __PARSERTOKEN_H__
#define __PARSERTOKEN_H__
#include "element.h"
#include "plane.h"

namespace DP {
class ParserToken {
    const Plane *_plan;
    bool _result;
    bool _error;

public:
    ParserToken(const Plane *plan);
    void setResult(bool result);
    bool getResult() const;
    Plane *getPlan() const;
    bool onError() const;
    void setError();
};
}

#endif /* __PARSERTOKEN_H__ */
