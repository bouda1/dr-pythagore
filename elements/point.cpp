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
