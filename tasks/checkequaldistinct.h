#ifndef __CHECKEQUALDISTINCT_H__
#define __CHECKEQUALDISTINCT_H__

class DPPlan;

class CheckEqualDistinct : public DPTask {
    DPPlan *_plan;

public:
    virtual void routine();
    CheckEqualDistinct(DPPlan *plan);
};

#endif /* __CHECKEQUALDISTINCT_H__ */
