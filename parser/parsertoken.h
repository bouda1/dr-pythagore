#ifndef __PARSERTOKEN_H__
#define __PARSERTOKEN_H__
#include "element.h"
#include "plane.h"

class DPParserToken {
    const DPPlane *_plan;
    bool _result;
    bool _error;

public:
    DPParserToken(const DPPlane *plan);
    void setResult(bool result);
    bool getResult() const;
    DPPlane *getPlan() const;
    bool onError() const;
    void setError();
};

#endif /* __PARSERTOKEN_H__ */
