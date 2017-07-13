#ifndef DPTREE_H
#define DPTREE_H
#include <string>
#include <vector>

namespace DP {

class Tree : public std::vector<Tree *>
{
    std::string _op;
    bool _leaf;

public:
    Tree(const std::string &op, int size, bool leaf = false);
    static Tree Not();
    static Tree And();
    static Tree Or();
};

inline Tree Tree::Not()
{
    return Tree("Not", 1);
}

inline Tree Tree::And()
{
    return Tree("And", 2);
}

inline Tree Tree::Or()
{
    return Tree("Or", 2);
}

}
#endif // DPTREE_H
