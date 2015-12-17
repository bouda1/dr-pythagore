#include <iostream>
#include "dpelement.h"

using namespace std;

DPElement::DPElement(DPPlan &parent)
    : _parent(parent)
{
}

DPElement::DPElement(DPPlan &parent, const char *name)
    : _parent(parent), _name(name)
{
}

void DPElement::setName(const string &newName)
{
    _name = newName;
}

const string &DPElement::getName(void) const
{
    return _name;
    //return _name;
}

DPPlan &DPElement::getParent() const
{
    return _parent;
}
