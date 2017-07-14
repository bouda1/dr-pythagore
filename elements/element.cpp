/* Dr-Pythagore
 * Copyright (C) 2016-2017 D. Boucher
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include "element.h"

using namespace std;
using namespace DP;

/**
 * @brief Element::Element  Constructor
 * @param parent The plane containing this element.
 */
Element::Element(Plane *parent)
    : _parent(parent)
{
}

/**
 * @brief Element::Element Constructor
 * @param parent The plane containing this element
 * @param name The name of this element
 */
Element::Element(Plane *parent, const char *name)
    : _parent(parent), _name(name)
{
}

/**
 * @brief Element::setName Set the name to this element
 * @param newName The new name
 */
void Element::setName(const string &newName)
{
    _name = newName;
}

/**
 * @brief Element::getName Returns the name of this element
 * @return A string containing the name
 */
const string &Element::getName(void) const
{
    return _name;
}

/**
 * @brief Element::getParent Returns the plane containing this element
 * @return A pointer to the plane
 */
Plane *Element::getParent() const
{
    return _parent;
}
