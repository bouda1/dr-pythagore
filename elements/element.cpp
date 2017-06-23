#include <iostream>
#include "element.h"

using namespace std;

DPElement::DPElement(DPPlane *parent)
    : _parent(parent)
{
}

DPElement::DPElement(DPPlane *parent, const char *name)
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
}

DPPlane *DPElement::getParent() const
{
    return _parent;
}
