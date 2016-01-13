#ifndef __DPTREE_H__
#define __DPTREE_H__

class DPTree {
    DPTree *parent;
    void *data;
    int start;
    int end;
    DPTree *left;
    DPTree *right;

public:
    DPTree(void(fillData *)(std::array<char> &data));
};

#endif /* __DPTREE_H__ */
