#ifndef __ACTION_H__
#define __ACTION_H__

class DPPool;

class DPAction {
    DPPool &_pool;

public:
    DPAction(DPPool &pool);

    void operator()() const;
};

#endif /* __ACTION_H__ */
