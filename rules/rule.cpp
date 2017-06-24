#include "rule.h"

using namespace std;

DPRule::DPRule(DPOpRel op, DPElement *a, DPElement *b, const std::string &explanation)
    : _op(op), _descr(explanation)
{
    _elems.push_back(a);
    _elems.push_back(b);
}

DPRule::DPRule(DPOpRel op, DPElement *a, DPElement *b, DPElement *c, const std::string &explanation)
    : _op(op), _descr(explanation)
{
    _elems.push_back(a);
    _elems.push_back(b);
    _elems.push_back(c);
}

DPElement *DPRule::get(int idx) const
{
    std::list<DPElement *>::const_iterator it = _elems.begin();

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

DPOpRel DPRule::getOp() const
{
    return _op;
}

const std::list<DPElement *> &DPRule::getElements() const
{
    return _elems;
}

const string &DPRule::getDescription() const
{
    return _descr;
}
