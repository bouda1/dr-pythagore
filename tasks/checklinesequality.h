#ifndef __CHECKLINESEQUALITY_H__
#define __CHECKLINESEQUALITY_H__

class DPPlan;

class CheckLinesEquality : public DPTask {
    DPPlan *_plan;

public:
    virtual void routine();
    CheckLinesEquality(DPPlan *plan);
};

#endif /* __CHECKLINESEQUALITY_H__ */
