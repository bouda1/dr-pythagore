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
