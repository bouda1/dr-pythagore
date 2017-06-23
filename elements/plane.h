#ifndef __PLAN_H__
#define __PLAN_H__
#include <deque>
#include <mutex>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include "pool.h"

class DPElement;
class DPPoint;
class DPLine;
class DPSegment;
class DPRule;

enum DPOpRel {
    OP_REL_DISTINCT,
    OP_REL_EQUALS,
    OP_REL_ORTHOGONAL,
    OP_REL_PARALLEL,
    OP_REL_COUNT
};

class DPPlane {

    std::unordered_set<DPLine *> _linesSet;
    std::unordered_set<DPSegment *> _segmentsSet;
    std::unordered_map<std::string, DPPoint *> _pointsList;

    mutable std::mutex _rules_mutex;
    std::set<DPRule *> _rules;

    mutable std::mutex _contradictions_mutex;
    std::deque<std::pair<DPRule *, DPRule *> > _contradictions;

    DPPool _pool;

public:
    DPPlane();
    DPPoint *getPoint(const char *a) const;
    DPLine *getLine(DPPoint *a, DPPoint *b);
    DPSegment *getSegment(DPPoint *a, DPPoint *b);
    void addPoint(DPPoint *a);
    void addLine(DPLine *a);
    void addSegment(DPSegment *a);
    bool pointExists(const char *a) const;
    void setRelation(DPOpRel op, DPElement *a, DPElement *b, const std::string &explanation);
    void setRelation(DPOpRel op, DPElement *a, DPElement *b, DPElement *c, const std::string &explanation);
    DPRule *hasRelation(DPOpRel op, DPElement *a, DPElement *b) const;
    std::deque<DPRule *> getRelations(DPOpRel op) const;
    void addContradiction(DPRule *a, DPRule *b);
    std::string getLastContradiction() const;
};

#endif /* __PLAN_H__ */
