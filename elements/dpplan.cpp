#include "dpplan.h"

using namespace std;

void DPPlan::setRelation(DPBinRel op, DPElement *a, DPElement *b)
{

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
