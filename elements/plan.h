#ifndef __PLAN_H__
#define __PLAN_H__
#include <deque>
#include <mutex>
#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include "pool.h"

class DPElement;
class DPPoint;
class DPLine;
class DPSegment;

enum DPBinRel {
    BIN_REL_DISTINCT,
    BIN_REL_EQUALS,
    BIN_REL_ORTHOGONAL,
    BIN_REL_PARALLEL,
    BIN_REL_COUNT
};

typedef std::tuple<DPBinRel, DPElement *, DPElement *, std::string> DPTRule;

class DPPlan {

    std::unordered_set<DPLine *> _linesSet;
    std::unordered_set<DPSegment *> _segmentsSet;
    std::unordered_map<std::string, DPPoint *> _pointsList;

    mutable std::mutex _rules_mutex;
    std::deque<DPTRule> _rules;

//    std::array<std::unordered_map<DPElement *,
//                                  std::unordered_set<DPElement *> >,
//               BIN_REL_COUNT> _rules;
    DPPool _pool;

public:
    DPPlan();
    DPPoint *getPoint(const char *a) const;
    DPLine *getLine(DPPoint *a, DPPoint *b);
    DPSegment *getSegment(DPPoint *a, DPPoint *b);
    void addPoint(DPPoint *a);
    void addLine(DPLine *a);
    void addSegment(DPSegment *a);
    bool pointExists(const char *a) const;
    void setRelation(DPBinRel op, DPElement *a, DPElement *b, const std::string &explanation);
    DPTRule *hasRelation(DPBinRel op, DPElement *a, DPElement *b) const;
    std::deque<DPTRule> getRelations(DPBinRel op) const;
};

#endif /* __PLAN_H__ */
