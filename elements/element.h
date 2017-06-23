#ifndef __ELEMENT_H__
#define __ELEMENT_H__
#include <string>
#include "plane.h"

class DPElement {
protected:
    std::string _name;
    DPPlane *_parent;

public:
    DPElement(DPPlane *parent);
    DPElement(DPPlane *parent, const char *name);
    void setName(const std::string &newName);
    const std::string &getName(void) const;
    DPPlane *getParent() const;
};

#endif /* __ELEMENT_H__ */

