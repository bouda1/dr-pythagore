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
#ifndef __LINE_H__
#define __LINE_H__
#include "set.h"

namespace DP {

class Line : public Set {
public:
    Line(Plane *parent, Point *a, Point *b);
    Line(Plane *parent, const char *a, const char *b);
    bool operator == (const Line &b) const;
    bool parallelTo(const Line &b) const;
};

}

#endif /* __LINE_H__ */
