#include <iostream>
#include "taskrule.h"
#include "rules/rule.h"
#include "plane_binding.h"

// FIXME: DEPRECATED FOR NOW

using namespace std;
using namespace DP;

TaskRule::TaskRule(DP::Plane *plane, DP::Rule *rule)
    : _plane(plane), _rule(rule)
{
    cout << "TaskRule constructor..." << endl;

}

void TaskRule::routine(lua_State *L)
{
    cout << "Routine of Task Rule" << endl;
    string op;
    switch (_rule->getOp()) {
     case OP_REL_ALIGNED:
        op = "Aligned";
        break;
    case OP_REL_DISTINCT:
        op = "Distinct";
        break;
    case OP_REL_EQUALS:
        op = "Equals";
        break;
    case OP_REL_NOTALIGNED:
        op = "NotAligned";
        break;
    case OP_REL_ORTHOGONAL:
        op = "Orthogonal";
        break;
    case OP_REL_PARALLEL:
        op = "Parallel";
        break;
    default:
        cerr << _rule->getOp() << " code not implemented in TaskRule routine" << endl;
        return;
    }

    lua_getglobal(L, op.c_str());
    if (!lua_isfunction(L, lua_gettop(L)))
        cerr << "Unable to find the " << op.c_str() << " function" << endl;
    else {
        int count = 0;
        for (Element *p : _rule->getElements()) {
            lua_pushstring(L, p->getName().c_str());
            count++;
        }
        lua_call(L, count, 2);
        string err;
        stackDump(L);
        if (lua_isboolean(L, -2)) {
            bool rep = lua_toboolean(L, -2);
            if (!rep) {
                err = lua_tostring(L, -1);
                std::cerr << err << std::endl;
                _plane->addContradiction(err);
            }
        }

    }
}
