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
#ifndef __POINT_H__
#define __POINT_H__
#include "element.h"

namespace DP {

class Point : public Element
{
private:
    virtual bool equal(const Element &b) const;
    virtual bool distinct(const Element &b) const;

public:
    Point(Plane *parent, const char *name);
};
}

#endif /* __POINT_H__ */
