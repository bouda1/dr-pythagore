#include "dpplan.h"
#include "dppoint.h"
#include "dpline.h"

using namespace std;

void DPPlan::setRelation(DPBinRel op, DPElement *a, DPElement *b)
{
    _rules[op][a].insert(b);
    _rules[op][b].insert(a);
}

bool DPPlan::hasRelation(DPBinRel op, DPPoint *a, DPPoint *b)
{
    unordered_map<DPElement *, unordered_set<DPElement *> >::iterator it;

    if (it != _rules[op].end()) {
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
    it = _pointsList.find(a);
    return (it != _pointsList.end());
}

DPPoint *DPPlan::getPoint(const char *a)
{
    unordered_map<string, DPPoint *>::iterator it;
    it = _pointsList.find(a);
    return (it != _pointsList.end()) ? it->second : nullptr;
}

DPLine *DPPlan::getLine(DPPoint *a, DPPoint *b)
{
    for (DPLine *l : _linesSet) {
        if (l->contains(a) && l->contains(b))
            return l;
    }

    return nullptr;
}

void DPPlan::addPoint(DPPoint *a)
{
    _pointsList[a->getName()] = a;
}

void DPPlan::addLine(DPLine *a)
{
    _linesSet.insert(a);
}
