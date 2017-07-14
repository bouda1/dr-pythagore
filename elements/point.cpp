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
#include "point.h"

using namespace std;
using namespace DP;

Point::Point(Plane *parent, const char *n)
    : Element(parent, n)
{
    cout << "\x1b[33;1m" << "New point " << n << "\x1b[0m" << endl;
    parent->addPoint(this);
}

bool Point::operator == (const Point &b)
{
    if (this == &b)
        return true;
    return getParent()->hasExpr("Equals", this, const_cast<Point *>(&b));
}

bool Point::operator != (const Point &b)
{
    if (this == &b)
        return false;
    return getParent()->hasExpr("Distinct", this, const_cast<Point *>(&b));
}
