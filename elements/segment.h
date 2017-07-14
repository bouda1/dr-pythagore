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
#ifndef __SEGMENT_H__
#define __SEGMENT_H__
#include "set.h"

namespace DP {

class Segment : public Set {
    Point *_beginPoint;
    Point *_endPoint;

public:
    Segment(Plane *parent, Point *a, Point *b);
    Segment(Plane *parent, const char *a, const char *b);
    bool operator == (const Segment &b);
    bool operator != (const Segment &b);
    void addPoint(Point *a);
    Point *getBegin() const;
    Point *getEnd() const;
};

}
#endif /* __SEGMENT_H__ */
