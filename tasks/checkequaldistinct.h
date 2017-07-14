#ifndef __CHECKEQUALDISTINCT_H__
#define __CHECKEQUALDISTINCT_H__

namespace DP {

class Plane;

class CheckEqualDistinct : public DPTask {
    Plane *_plan;

public:
    virtual void routine(lua_State *L);
    CheckEqualDistinct(Plane *plan);
};

}
#endif /* __CHECKEQUALDISTINCT_H__ */
