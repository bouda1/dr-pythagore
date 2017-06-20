#include "rule.h"

using namespace std;

DPRule::DPRule(DPBinRel op, DPElement *a, DPElement *b, const std::string &explanation)
    : _op(op), _descr(explanation)
{
    _elems.push_back(a);
    _elems.push_back(b);
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

DPBinRel DPRule::getOp() const
{
    return _op;
}

const string &DPRule::getDescription() const
{
    return _descr;
}
