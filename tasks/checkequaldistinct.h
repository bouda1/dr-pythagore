#ifndef __CHECKEQUALDISTINCT_H__
#define __CHECKEQUALDISTINCT_H__

class Plane;

namespace DP {

class CheckEqualDistinct : public DPTask {
    Plane *_plan;

public:
    virtual void routine(lua_State *L);
    CheckEqualDistinct(Plane *plan);
};

}
#endif /* __CHECKEQUALDISTINCT_H__ */
