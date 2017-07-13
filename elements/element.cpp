#include <iostream>
#include "element.h"

using namespace std;
using namespace DP;

Element::Element(Plane *parent)
    : _parent(parent)
{
}

Element::Element(Plane *parent, const char *name)
    : _parent(parent), _name(name)
{
}

void Element::setName(const string &newName)
{
    _name = newName;
}

const string &Element::getName(void) const
{
    return _name;
}

Plane *Element::getParent() const
{
    return _parent;
}
