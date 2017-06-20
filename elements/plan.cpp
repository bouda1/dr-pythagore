#include <iostream>
#include "plan.h"
#include "point.h"
#include "line.h"
#include "segment.h"
#include "checkequaldistinct.h"
#include "rules/rule.h"

using namespace std;

DPPlan::DPPlan()
    : _pool()
{}

deque<DPRule *> DPPlan::getRelations(DPBinRel op) const
{
    unique_lock<mutex> lock(_rules_mutex);
    deque<DPRule *> retval = deque<DPRule *>();
    for (DPRule *r : _rules) {
        if (r->getOp() == op)
            retval.push_back(r);
    }
    return retval;
}

void DPPlan::setRelation(DPBinRel op, DPElement *a, DPElement *b, const string &explanation)
{
    _rules_mutex.lock();
    DPRule *rule = new DPRule(op, a, b, explanation);
    _rules.insert(rule);
    _rules_mutex.unlock();

    if (op == BIN_REL_DISTINCT || op == BIN_REL_EQUALS)
        _pool.enqueueTask(new CheckEqualDistinct(this));
}

void DPPlan::setRelation(DPBinRel op, DPElement *a, DPElement *b, DPElement *c, const std::string &explanation)
{
    _rules_mutex.lock();
    DPRule *r = new DPRule(op, a, b, explanation);
    _rules.insert(r);
    _rules_mutex.unlock();

    if (op == BIN_REL_DISTINCT || op == BIN_REL_EQUALS)
        _pool.enqueueTask(new CheckEqualDistinct(this));
}

DPRule *DPPlan::hasRelation(DPBinRel op, DPElement *a, DPElement *b) const
{
    {
        unique_lock<mutex> lock(_rules_mutex);
        for (DPRule *rule : _rules) {
            if (rule->getOp() == op) {
                if (rule->get(0) == a && rule->get(1) == b)
                    return rule;
                else if (rule->get(0) == b && rule->get(1) == a)
                    return rule;
            }
        }
    }
    return nullptr;
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

void DPPlan::addContradiction(DPRule *a, DPRule *b)
{
    unique_lock<mutex> lock(_contradictions_mutex);
    _contradictions.push_back(pair<DPRule *, DPRule *>(a, b));
}

string DPPlan::getLastContradiction() const
{
    unique_lock<mutex> lock(_contradictions_mutex);
    pair<DPRule *, DPRule *> c = _contradictions.back();
    string retval = "<< " + c.first->getDescription() + " >> not compatible with << " + c.second->getDescription() + " >>";
    return retval;
}

