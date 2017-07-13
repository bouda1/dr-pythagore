#ifndef TASKRULE_H
#define TASKRULE_H
#include "task.h"

// FIXME: DEPRECATED FOR NOW

namespace DP {

class Plane;
class Rule;

class TaskRule : public DPTask {
    Plane *_plane;
    Rule *_rule;

public:
    TaskRule(Plane *plane, Rule *rule);
    virtual void routine(lua_State *L);
};

}

#endif // TASKRULE_H
