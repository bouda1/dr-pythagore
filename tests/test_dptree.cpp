#include <iostream>
#include <string>
#include "dptree.h"
#include "test_dptree.h"

using namespace std;

void TestDPTree::setUp()
{
}

void TestDPTree::tearDown()
{
}

int TestDPTree::getBit(int *treeData, int range)
{
    return ((*treeData) & (1 << range)) != 0;
}

int TestDPTree::compareData(int *treeData, int *userData, int start, int end, DPTree<int>::DPTreeContinue &cont)
{
    int i, bit;
    if (treeData == nullptr)
        return -1;
    for (i = start, bit = 1 << start; i < end; i++, bit <<= 1) {
        if ((*treeData & bit) != (*userData & bit)) {
            cont = (*userData & bit) ? DPTree<int>::DPTreeRight : DPTree<int>::DPTreeLeft;
            return i;
        }
    }
    if (i < 32)
        cont = (*userData & bit) ? DPTree<int>::DPTreeRight : DPTree<int>::DPTreeLeft;
    else
        cont = DPTree<int>::DPTreeLeaf;

    return i;
}

void TestDPTree::testTreeSize()
{
    DPTree<int> tree(TestDPTree::getBit, TestDPTree::compareData, sizeof(int) << 3);

    for (int i = 0; i < 10; i++) {
        tree.insert(new int(i));
    }
    cout << endl << " ***** Tree size : " << tree.size() << " ***** " << endl;
    CPPUNIT_ASSERT(tree.size() == 10);
}

