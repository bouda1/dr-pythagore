#ifndef __DPTREE_H__
#define __DPTREE_H__

enum DPNodeContinue {
    DPNodeLeaf,
    DPNodeLeft,
    DPNodeRight
};

template <typename T>
class DPTree;

template <typename T>
class DPNode {
private:
    DPTree<T> *_root;
    DPNode<T> *_parent;
    DPNode<T> *_left;
    DPNode<T> *_right;
    T *_data;
    int _start;
    int _end;
    bool _leaf;

protected:
    DPTree<T> *getRoot() const;
    DPNode<T> *getParent() const;
    void replaceInParents(T *oldData, T *newData);
    bool isLeaf() const;

public:
    void setStart(int start)
    {
        _start = start;
    }
    void setEnd(int end)
    {
        _end = end;
    }
    void setData(T *data)
    {
        _data = data;
    }
    void setLeaf(bool leaf)
    {
        _leaf = leaf;
    }
    int size() const
    {
        int retval = (isLeaf() ? 1 : 0) + (_left ? _left->size() : 0) + (_right ? _right->size() : 0);
        return retval;
    }
    DPNode(DPTree<T> *root);
    void insert(T *data);
};

template <typename T>
class DPTree {
private:
    DPNode<T> *_left;
    DPNode<T> *_right;
    int _maxKeyLength;

public:
    int (*_getBit)(T *, int);
    int (*_compareData)(T *, T *, int, int, DPNodeContinue &);
    DPTree(int (*getBit)(T *, int),
           int (*compareData)(T *, T *, int, int, DPNodeContinue &),
           int maxKeyLength);
    int size() const
    {
        return (_left ? _left->size() : 0) + (_right ? _right->size() : 0);
    }
    int getMaxKeyLength() const
    {
        return _maxKeyLength;
    }
    void insert(T *data);
};

template <typename T>
DPNode<T>::DPNode(DPTree<T> *root)
    : _root(root)
    , _parent(nullptr)
    , _left(nullptr)
    , _right(nullptr)
    , _data(nullptr)
    , _start(0)
    , _end(0)
    , _leaf(false)
{
}

template <typename T>
bool DPNode<T>::isLeaf() const
{
    return _leaf;
}

template <typename T>
DPNode<T> *DPNode<T>::getParent() const
{
    return _parent;
}

template <typename T>
DPTree<T> *DPNode<T>::getRoot() const
{
    return _root;
}

template <typename T>
void DPNode<T>::replaceInParents(T *oldData, T *newData)
{
    if (_data == oldData)
        _data = newData;
    DPNode<T> *parent = getParent();
    while (parent) {
        parent->replaceInParents(oldData, newData);
        parent = parent->getParent();
    }
}

template <typename T>
DPTree<T>::DPTree(int (*getBit)(T *, int),
                  int (*compareData)(T *, T *, int, int, DPNodeContinue &),
                  int maxKeyLength)
    : _left(nullptr)
    , _right(nullptr)
    , _getBit(getBit)
    , _compareData(compareData)
    , _maxKeyLength(maxKeyLength)
{
}

template <typename T>
void DPNode<T>::insert(T *data)
{
    DPNodeContinue cont;
    int cmp = getRoot()->_compareData(_data, data, _start, _end, cont);
    /* Here nothing to compare, the tree is empty */
    if (cmp == -1) {
        _data = data;
        _start = 0;
        _end = getRoot()->getMaxKeyLength();
    }
    /* They are equal on the range from _start to _end */
    else if (cmp == _end) {
        switch (cont) {
        case DPNodeLeft:
            if (!_left)
                _left = new DPNode<T>(_root);
            _left->insert(data);
            break;
        case DPNodeRight:
            if (!_right)
                _right = new DPNode<T>(_root);
            _right->insert(data);
            break;
        case DPNodeLeaf:
            if (isLeaf()) {
                /* We already are a leaf, it is replaced by the new value */
                replaceInParents(_data, data);
                delete _data;
            }
            else {
                setLeaf(true);
                _data = data;
            }
        }
    }
    else {
        DPNode *newActual = new DPNode<T>(_root);
        newActual->setStart(cmp);
        newActual->setEnd(_end);
        newActual->setData(_data);
        newActual->setLeaf(_leaf);

        DPNode *newUser = new DPNode<T>(_root);
        newUser->setStart(cmp);
        newUser->setEnd(_end);
        newUser->setData(data);
        newUser->setLeaf(true);
        _end = cmp;
        _leaf = false;

        switch (cont) {
        case DPNodeLeft:
            _left = newActual;
            _right = newUser;
            break;
        case DPNodeRight:
            _right = newActual;
            _left = newUser;
            break;
        case DPNodeLeaf:
            abort();
        }
    }
}

template <typename T>
void DPTree<T>::insert(T *data)
{
    DPNodeContinue cont;
    int first = _getBit(data, 0);

    if (first == 0)
        /* this data should go on the left */
        if (!_left) {
            _left = new DPNode<T>(this);
            _left->setStart(0);
            _left->setEnd(_maxKeyLength);
            _left->setData(data);
            _left->setLeaf(true);
        }
        else
            _left->insert(data);
    else {
        /* this data should go on the right */
        if (!_right) {
            _right = new DPNode<T>(this);
            _right->setStart(0);
            _right->setEnd(_maxKeyLength);
            _right->setData(data);
            _right->setLeaf(true);
        }
        else
            _right->insert(data);
    }
}

#endif /* __DPTREE_H__ */
