#include <sstream>
#include "plane.h"
#include "line.h"
#include "point.h"
#include "simpleExpr.h"

using namespace std;
using namespace DP;

Line::Line(Plane *parent, Point *a, Point *b)
    : Set(parent)
{
    stringstream ss;
    ss << '(' << a->getName() << b->getName() << ')';
    setName(ss.str());

    ss << " is a line";

    /* We must assume points are distinct */
    SimpleExpr *expr = new SimpleExpr("Distinct", a, b, ss.str());
    _parent->addExpression(expr);

    addPoint(a);
    addPoint(b);
    _parent->addLine(this);
}

Line::Line(Plane *parent, const char *a, const char *b)
    : Set(parent)
{
    Point *aa, *bb;

    if (_parent->pointExists(a))
        aa = _parent->getPoint(a);
    else
        aa = new Point(parent, a);

    if (_parent->pointExists(b))
        bb = _parent->getPoint(b);
    else
        bb = new Point(parent, b);

    stringstream ss;
    ss << '(' << a << b << ')';
    setName(ss.str());

    ss << " is a line";

    /* We must assume points are distinct. */
    SimpleExpr *simp = new SimpleExpr("Distinct", aa, bb, ss.str());
    _parent->addExpression(simp);
//    _parent->setRelation(OP_REL_DISTINCT, aa, bb, ss.str());

    addPoint(aa);
    addPoint(bb);
    _parent->addLine(this);
}

bool Line::operator == (const Line &b) const
{
    int count = 0;
    Point *first_point = nullptr;

    for (Point *p : _singlePoints) {
        if (count == 0 && b.contains(p)) {
            count++;
            first_point = p;
        }
        else if (count > 0 && *p != *first_point && b.contains(p))
            return true;
    }
    return false;
}

bool Line::parallelTo(const Line &b) const
{
    return getParent()->hasExpr("Parallel", const_cast<Line *>(this), const_cast<Line *>(&b));
}
