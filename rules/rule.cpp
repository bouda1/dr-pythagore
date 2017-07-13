#include "rule.h"

// FIXME: DEPRECATED NOW

using namespace std;
using namespace DP;

DP::Rule::Rule(DPOpRel op, Element *a, Element *b, const std::string &explanation)
    : _op(op), _descr(explanation)
{
    _elems.push_back(a);
    _elems.push_back(b);
}

DP::Rule::Rule(DPOpRel op, Element *a, Element *b, Element *c, const std::string &explanation)
    : _op(op), _descr(explanation)
{
    _elems.push_back(a);
    _elems.push_back(b);
    _elems.push_back(c);
}

Element *DP::Rule::get(int idx) const
{
    std::list<Element *>::const_iterator it = _elems.begin();

    switch (idx) {
    case 0:
        return *it;
    case 1:
        ++it;
        return *it;
    case 2:
        return _elems.back();
    }

    return nullptr;
}

DPOpRel DP::Rule::getOp() const
{
    return _op;
}

const std::list<Element *> &DP::Rule::getElements() const
{
    return _elems;
}

const string &DP::Rule::getDescription() const
{
    return _descr;
}
