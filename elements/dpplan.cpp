#include "dpplan.h"
#include "dppoint.h"

using namespace std;

void DPPlan::setRelation(DPBinRel op, DPElement *a, DPElement *b)
{
    m_rules[op][a].insert(b);
    m_rules[op][b].insert(a);
}

bool DPPlan::hasRelation(DPBinRel op, DPPoint *a, DPPoint *b)
{
    unordered_map<DPElement *, unordered_set<DPElement *> >::iterator it;

    if (it != m_rules[op].end()) {
        unordered_set<DPElement *>::iterator sit = it->second.find(b);
        if (sit != it->second.end()) {
            return true;
        }
    }
    return false;
}

bool DPPlan::pointExists(const char *a)
{
    unordered_map<string, DPPoint *>::iterator it;
    it = m_pointsList.find(a);
    return (it != m_pointsList.end());
}

DPPoint *DPPlan::getPoint(const char *a)
{
    unordered_map<string, DPPoint *>::iterator it;
    it = m_pointsList.find(a);
    return (it != m_pointsList.end()) ? it->second : nullptr;
}

DPLine *DPPlan::getLine(DPPoint *a, DPPoint *b)
{
    /* We have to verify that those two points exist and are distinct */
    /* If there is a line containing those two points, we can take it */
    /* Otherwise, we create the line and return it */
    return nullptr;
}

void DPPlan::addPoint(DPPoint *a)
{
    m_pointsList[a->getName()] = a;
}
