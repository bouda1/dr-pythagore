#ifndef __POINT_H__
#define __POINT_H__
#include "element.h"

namespace DP {

class Point : public Element
{
    public:
        Point(Plane *parent, const char *name);
        bool operator == (const Point &b);
        bool operator != (const Point &b);
};

}

#endif /* __POINT_H__ */
