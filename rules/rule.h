#ifndef DPRULE_H
#define DPRULE_H
#include <list>
#include <string>
#include "element.h"

class DPRule
{
    DPBinRel _op;
    std::list<DPElement *> _elems;
    std::string _descr;

public:
    DPRule(DPBinRel op, DPElement *a, DPElement *b, const std::string &explanation);
    DPElement *get(int idx) const;
    DPBinRel getOp() const;
    const std::string &getDescription() const;
};

#endif // DPRULE_H
