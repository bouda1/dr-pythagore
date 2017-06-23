#ifndef __CHECKEQUALDISTINCT_H__
#define __CHECKEQUALDISTINCT_H__

class DPPlane;

class CheckEqualDistinct : public DPTask {
    DPPlane *_plan;

public:
    virtual void routine();
    CheckEqualDistinct(DPPlane *plan);
};

#endif /* __CHECKEQUALDISTINCT_H__ */
