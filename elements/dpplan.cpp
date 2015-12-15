#include "dpplan.h"
#include "dppoint.h"

using namespace std;

void DPPlan::setRelation(DPBinRel op, DPElement *a, DPElement *b)
{
    // pas bon : on peut avoir a en relation avec plusieurs b sur une même
    // relation.
    m_rules[op][a] = b;
    m_rules[op][b] = a;
}

bool DPPlan::hasRelation(DPBinRel op, DPPoint *a, DPPoint *b)
{
    unordered_map<DPElement *, DPElement *>::iterator it;

    it = m_rules[op].find(static_cast<DPElement *>(a));
    if (it != m_rules[op].end()) {
        if (it->first->getName() == b->getName())
            return true;
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
