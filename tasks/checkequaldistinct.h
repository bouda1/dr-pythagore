#ifndef __CHECKEQUALDISTINCT_H__
#define __CHECKEQUALDISTINCT_H__

class DPPlan;

class CheckEqualDistinct : public DPTask {
    const DPPlan &_plan;

public:
    virtual void routine();
    CheckEqualDistinct(const DPPlan &plan);
};

#endif /* __CHECKEQUALDISTINCT_H__ */
