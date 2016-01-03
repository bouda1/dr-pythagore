#include <iostream>
#include "plan.h"
#include "point.h"
#include "line.h"
#include "segment.h"
#include "checkequaldistinct.h"

using namespace std;

DPPlan::DPPlan()
    : _pool()
{}

unordered_map<DPElement *, unordered_set<DPElement *> >DPPlan::getRelations(DPBinRel op) const
{
    unique_lock<mutex> lock(_rules_mutex);
    return _rules[op];
}

void DPPlan::setRelation(DPBinRel op, DPElement *a, DPElement *b)
{
    _rules_mutex.lock();
    _rules[op][a].insert(b);
    _rules_mutex.unlock();

    if (op == BIN_REL_DISTINCT || op == BIN_REL_EQUALS)
        _pool.enqueueTask(new CheckEqualDistinct(this));
}

bool DPPlan::hasRelation(DPBinRel op, DPElement *a, DPElement *b) const
{
    unordered_map<DPElement *, unordered_set<DPElement *> >::const_iterator it;

    {
        unique_lock<mutex> lock(_rules_mutex);
        it = _rules[op].find(a);
        if (it == _rules[op].end()) {
            DPElement *tmp = a;
            a = b;
            b = tmp;
            it = _rules[op].find(a);
        }
        if (it != _rules[op].end()) {
            unordered_set<DPElement *>::const_iterator sit = it->second.find(b);
            if (sit != it->second.end()) {
                return true;
            }
        }
    }
    return false;
}

bool DPPlan::pointExists(const char *a) const
{
    unordered_map<string, DPPoint *>::const_iterator it;
    it = _pointsList.find(a);
    return (it != _pointsList.end());
}

DPPoint *DPPlan::getPoint(const char *a) const
{
    unordered_map<string, DPPoint *>::const_iterator it;
    it = _pointsList.find(a);
    return (it != _pointsList.end()) ? it->second : nullptr;
}

DPLine *DPPlan::getLine(DPPoint *a, DPPoint *b)
{
    DPLine *retval = nullptr;
    if (*a != *b) {
        for (DPLine *l : _linesSet) {
            if (l->contains(a) && l->contains(b))
                return l;
        }

        /* It is not already defined, but we can do it since we have the
         * points and they are distinct */
        retval = new DPLine(this, a, b);
    }
    return retval;
}

DPSegment *DPPlan::getSegment(DPPoint *a, DPPoint *b)
{
    DPSegment *retval = nullptr;
    if (*a != *b) {
        for (DPSegment *s : _segmentsSet) {
            DPPoint *begin = s->getBegin();
            DPPoint *end = s->getEnd();
            if ((*begin == *a && *end == *b)
                || (*begin == *b && *end == *a))
                return s;
        }

        /* It is not already defined, but we can do it since we have the
         * points and they are distinct */
        retval = new DPSegment(this, a, b);
    }
    return retval;
}

void DPPlan::addPoint(DPPoint *a)
{
    _pointsList[a->getName()] = a;
}

void DPPlan::addLine(DPLine *a)
{
    _linesSet.insert(a);
}

void DPPlan::addSegment(DPSegment *a)
{
    _segmentsSet.insert(a);
}

