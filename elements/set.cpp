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
#include "set.h"
#include "point.h"

using namespace std;
using namespace DP;

Set::Set(Plane *parent)
    : Element(parent)
    , _singlePoints()
{
}

bool Set::contains(Point *point, bool fast) const
{
    cout << "Set::contains point " << point->getName() << endl;
    unique_lock<mutex> lock(_singlePointsMutex);
    unordered_set<Point *>::const_iterator it = _singlePoints.find(point);

    if (it != _singlePoints.end())
        return true;

    if (!fast) {
        Element *a = static_cast<Element *>(point);
        Element *b = static_cast<Element *>(const_cast<Set *>(this));
        return _parent->hasExpr("Element", a, b);
    }
    return false;
}

void Set::addPoint(Point *a)
{
    unique_lock<mutex> lock(_singlePointsMutex);
    _singlePoints.insert(a);
}

unordered_set<Point *> Set::getSinglePoints() const
{
    unique_lock<mutex> lock(_singlePointsMutex);
    return _singlePoints;
}
