#ifndef __CHECKLINESEQUALITY_H__
#define __CHECKLINESEQUALITY_H__

class Plane;

class CheckLinesEquality : public DPTask {
    Plane *_plan;

public:
    virtual void routine(lua_State *L);
    CheckLinesEquality(Plane *plan);
};

#endif /* __CHECKLINESEQUALITY_H__ */
