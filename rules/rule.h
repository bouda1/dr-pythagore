#ifndef DPRULE_H
#define DPRULE_H
#include <list>
#include <string>
#include "element.h"

// FIXME: DEPRECATED NOW

namespace DP {

class Rule
{
    DPOpRel _op;
    std::list<Element *> _elems;
    std::string _descr;

public:
    Rule(DPOpRel op, Element *a, Element *b, const std::string &explanation);
    Rule(DPOpRel op, Element *a, Element *b, Element *c, const std::string &explanation);
    Element *get(int idx) const;
    DPOpRel getOp() const;
    const std::list<Element *>& getElements() const;
    const std::string &getDescription() const;
};

}

#endif // DPRULE_H
