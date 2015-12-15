#ifndef __DPPLAN_H__
#define __DPPLAN_H__
#include <array>
#include <unordered_map>

class DPElement;
class DPPoint;

enum DPBinRel {
    BIN_REL_DISTINCT,
    BIN_REL_EQUALS,
    BIN_REL_ORTHOGONAL,
    BIN_REL_PARALLEL,
    BIN_REL_COUNT
};

class DPPlan {

    std::unordered_map<std::string, DPPoint *> m_pointsList;
    std::array<std::unordered_map<DPElement *, DPElement *> , BIN_REL_COUNT> m_rules;

public:
    DPPoint *getPoint(const char *a);
    bool pointExists(const char *a);
    void setRelation(DPBinRel op, DPElement *a, DPElement *b);
    bool hasRelation(DPBinRel op, DPPoint *a, DPPoint *b);
};

#endif /* __DPPLAN_H__ */
