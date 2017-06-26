#ifndef __CHECKLINESEQUALITY_H__
#define __CHECKLINESEQUALITY_H__

class DPPlane;

class CheckLinesEquality : public DPTask {
    DPPlane *_plan;

public:
    virtual void routine(lua_State *L);
    CheckLinesEquality(DPPlane *plan);
};

#endif /* __CHECKLINESEQUALITY_H__ */
