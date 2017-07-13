#include <vector>
#include "tree.h"

using namespace std;
using namespace DP;

Tree::Tree(const std::string &op, int size, bool leaf) :
    vector(size), _op(op), _leaf(leaf)
{
}

