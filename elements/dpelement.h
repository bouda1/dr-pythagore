#ifndef __DPELEMENT_H__
#define __DPELEMENT_H__
#include <string>
#include "dpplan.h"

class DPElement {
protected:
    std::string _name;
    DPPlan &_parent;

public:
    DPElement(DPPlan &parent);
    DPElement(DPPlan &parent, const char *name);
    void setName(const std::string &newName);
    std::string &getName(void);
    DPPlan &getParent() const;
};

#endif /* __DPELEMENT_H__ */

