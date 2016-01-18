#ifndef __DPTREE_H__
#define __DPTREE_H__
#include <vector>

template <typename T>
class DPTree {
public:
    enum DPTreeContinue {
        DPTreeLeaf,
        DPTreeLeft,
        DPTreeRight
    };

private:
    DPTree *_parent;
    DPTree *_left;
    DPTree *_right;
    int (*_getBit)(T *, int);
    int (*_compareData)(T *, T *, int, int, DPTreeContinue &);
    T *_data;
    int _start;
    int _end;
    int _maxKeyLength;
    bool _leaf;

protected:
    DPTree *getParent() const;
    void replaceInParents(T *oldData, T *newData);
    bool isLeaf() const;
    void setLeaf(bool leaf);
    void setStart(int start);
    void setEnd(int end);
    void setData(T *data);
    void insertNode(T *data);

public:
    DPTree(int (*getBit)(T *, int),
           int (*compareData)(T *, T *, int, int, DPTreeContinue &),
           int maxKeyLength);
    void insert(T *data);
    int size() const
    {
        int retval = (isLeaf() ? 1 : 0) + (_left ? _left->size() : 0) + (_right ? _right->size() : 0);
        return retval;
    }
};

template<typename T>
bool DPTree<T>::isLeaf() const
{
    return _leaf;
}

template<typename T>
void DPTree<T>::setLeaf(bool leaf)
{
    _leaf = leaf;
}

template<typename T>
void DPTree<T>::setStart(int start)
{
    _start = start;
}

template<typename T>
void DPTree<T>::setEnd(int end)
{
    _end = end;
}

template<typename T>
void DPTree<T>::setData(T *data)
{
    _data = data;
}

template<typename T>
DPTree<T> *DPTree<T>::getParent() const
{
    return _parent;
}

template <typename T>
void DPTree<T>::replaceInParents(T *oldData, T *newData)
{
    if (_data == oldData)
        _data = newData;
    DPTree<T> *parent = getParent();
    while (parent) {
        parent->replaceInParents(oldData, newData);
        parent = parent->getParent();
    }
}

template <typename T>
DPTree<T>::DPTree(int (*getBit)(T *, int),
                  int (*compareData)(T *, T *, int, int, DPTreeContinue &),
                  int maxKeyLength)
    : _parent(nullptr)
    , _left(nullptr)
    , _right(nullptr)
    , _getBit(getBit)
    , _compareData(compareData)
    , _data(nullptr)
    , _start(0), _end(0)
    , _leaf(false)
    , _maxKeyLength(maxKeyLength)
{
}

template <typename T>
void DPTree<T>::insertNode(T *data)
{
    DPTreeContinue cont;
    int cmp = _compareData(_data, data, _start, _end, cont);
    /* Here nothing to compare, the tree is empty */
    if (cmp == -1) {
        _data = data;
        _start = 0;
        _end = _maxKeyLength;
    }
    /* They are equal on the range from _start to _end */
    else if (cmp == _end) {
        switch (cont) {
        case DPTreeLeft:
            if (!_left)
                _left = new DPTree<T>(_getBit, _compareData, _maxKeyLength);
            _left->insertNode(data);
            break;
        case DPTreeRight:
            if (!_right)
                _right = new DPTree<T>(_getBit, _compareData, _maxKeyLength);
            _right->insertNode(data);
            break;
        case DPTreeLeaf:
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
        DPTree *newActual = new DPTree<T>(_getBit, _compareData, _maxKeyLength);
        newActual->setStart(cmp);
        newActual->setEnd(_end);
        newActual->setData(_data);
        newActual->setLeaf(_leaf);

        DPTree *newUser = new DPTree<T>(_getBit, _compareData, _maxKeyLength);
        newUser->setStart(cmp);
        newUser->setEnd(_end);
        newUser->setData(data);
        newUser->setLeaf(true);
        _end = cmp;
        _leaf = false;

        switch (cont) {
        case DPTreeLeft:
            _left = newActual;
            _right = newUser;
            break;
        case DPTreeRight:
            _right = newActual;
            _left = newUser;
            break;
        case DPTreeLeaf:
            abort();
        }
    }
}

template <typename T>
void DPTree<T>::insert(T *data)
{
    DPTreeContinue cont;
    // Le noeud root a un comportement particulier : il ne doit pas contenir de data sinon on a un problème avec deux donées commençant par une valeur différente puisqu'on ne peut en stocker qu'une seule.
    // On pourrait imaginer que dans ce cas la longueur de la clé considérée soit nulle afin de passer aux deux noeuds enfants mais ce fonctionnement ne fonctionnera pas ensuite avec les sous-noeuds. Et l'insertion étant récursive, on casse le fonctionnement.
    // Le noeud root est donc vide.
    // Si l'enfant commence par un 0, il va partir sur la gauche, s'il commence par un 1, il part sur la droite.
    // Le noeud actuel contient ou pas un pointeur vers un noeud.
    // On a deux entiers _start et _end permettant de connaître une portion de la clé.
    // La clé n'est pas connue directement mais par une fonction externe y donnant accès.
    // On a aussi une fonction permettant de comparer deux objets de type T sur le range _start.._end.
    //
    // On commence par comparer les deux clés (celle stockée et celle à insérer) sur le range voulu.
    // Egalité:
    //      - On a fini la clé à insérer : C'est ici qu'il faut insérer la valeur
    //      - On n'a pas fini la clé : le prochain est un 1, on part sur la branche de droite
    //                                 le prochain est un 0, on part sur la branche de gauche
    // Différence:
    //      - On coupe la stockée actuelle de manière à conserver la partie commune au deux dans la première partie.
    //      - On insère celle continuant avec un 0 à gauche et celle avec un 1 à droite.
    //
    int first = _getBit(data, 0);

    if (first == 0)
        /* this data should go on the left */
        if (!_left) {
            _left = new DPTree(_getBit, _compareData, _maxKeyLength);
            _left->setStart(_start);
            _left->setEnd(_maxKeyLength);
            _left->setData(data);
            _left->setLeaf(true);
        }
        else
            _left->insertNode(data);
    else {
        /* this data should go on the right */
        if (!_right) {
            _right = new DPTree(_getBit, _compareData, _maxKeyLength);
            _right->setStart(_start);
            _right->setEnd(_maxKeyLength);
            _right->setData(data);
            _right->setLeaf(true);
        }
        else
            _right->insertNode(data);
    }
}

#endif /* __DPTREE_H__ */
