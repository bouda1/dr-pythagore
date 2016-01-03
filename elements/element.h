#ifndef __ELEMENT_H__
#define __ELEMENT_H__
#include <string>
#include "plan.h"

class DPElement {
protected:
    std::string _name;
    DPPlan *_parent;

public:
    DPElement(DPPlan *parent);
    DPElement(DPPlan *parent, const char *name);
    void setName(const std::string &newName);
    const std::string &getName(void) const;
    DPPlan *getParent() const;
};

#endif /* __ELEMENT_H__ */
