#ifndef __ELEMENT_H__
#define __ELEMENT_H__
#include <string>
#include "plane.h"

namespace DP {

class Element {
protected:
    std::string _name;
    Plane *_parent;

public:
    Element(Plane *parent);
    Element(Plane *parent, const char *name);
    void setName(const std::string &newName);
    const std::string &getName(void) const;
    Plane *getParent() const;
};

}

#endif /* __ELEMENT_H__ */

