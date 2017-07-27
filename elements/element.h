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
#ifndef __ELEMENT_H__
#define __ELEMENT_H__
#include <string>
#include "plane.h"

namespace DP {

class Element
{
private:
    virtual bool equal(const Element &e) const = 0;
    virtual bool distinct(const Element &e) const = 0;

protected:
    Plane *_parent;
    std::string _name;

public:
    Element(Plane *parent);
    Element(Plane *parent, const char *name);
    void setName(const std::string &newName);
    const std::string &getName(void) const;
    Plane *getParent() const;

    bool operator==(const Element &e) const;
    bool operator!=(const Element &e) const;
};
}

#endif /* __ELEMENT_H__ */
