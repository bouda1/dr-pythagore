#ifndef DPRULE_H
#define DPRULE_H
#include <list>
#include <string>
#include "element.h"

class DPRule
{
    DPOpRel _op;
    std::list<DPElement *> _elems;
    std::string _descr;

public:
    DPRule(DPOpRel op, DPElement *a, DPElement *b, const std::string &explanation);
    DPRule(DPOpRel op, DPElement *a, DPElement *b, DPElement *c, const std::string &explanation);
    DPElement *get(int idx) const;
    DPOpRel getOp() const;
    const std::string &getDescription() const;
};

#endif // DPRULE_H
