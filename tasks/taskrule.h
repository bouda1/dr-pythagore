#ifndef TASKRULE_H
#define TASKRULE_H
#include "task.h"

class DPPlane;
class DPRule;

class TaskRule : public DPTask {
    DPPlane *_plane;
    DPRule *_rule;

public:
    TaskRule(DPPlane *plane, DPRule *rule);
    virtual void routine(lua_State *L);
};

#endif // TASKRULE_H
