#include <iostream>
#include "taskrule.h"
#include "rules/rule.h"

using namespace std;

TaskRule::TaskRule(DPPlane *plane, DPRule *rule)
    : _plane(plane), _rule(rule)
{
    cout << "TaskRule constructor..." << endl;

}

void TaskRule::routine(lua_State *L)
{
    cout << "Routine of Task Rule" << endl;
    switch (_rule->getOp()) {
        case OP_REL_ALIGNED:
            lua_getglobal(L, "Aligned");
            if (!lua_isfunction(L, lua_gettop(L)))
                cerr << "Unable to find the Aligned function" << endl;
            else {
                int count = 0;
                for (DPElement *p : _rule->getElements()) {
                    lua_pushstring(L, p->getName().c_str());
                    count++;
                }
                lua_call(L, count, 0);
            }
            break;
        default:
            cerr << "Not implemented..." << endl;
    }
}
