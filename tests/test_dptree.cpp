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

int TestDPTree::compareData(int *treeData, int *userData, int start, int end, DPNodeContinue &cont)
{
    int i, bit;
    if (treeData == nullptr)
        return -1;
    for (i = start, bit = 1 << start; i < end; i++, bit <<= 1) {
        if ((*treeData & bit) != (*userData & bit)) {
            cont = (*userData & bit) ? DPNodeRight : DPNodeLeft;
            return i;
        }
    }
    if (i < 32)
        cont = (*userData & bit) ? DPNodeRight : DPNodeLeft;
    else
        cont = DPNodeLeaf;

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

    for (int j = 0; j < 10; j++) {
        int *ret = tree.lookup(&j);
        CPPUNIT_ASSERT(ret);
        if (ret)
            CPPUNIT_ASSERT(j == *ret);
    }
}

void TestDPTree::testTreeInsert()
{
    int array[] = { 0, 186, 90, 53, 877, 3277, 621 };

    DPTree<int> tree(TestDPTree::getBit, TestDPTree::compareData, sizeof(int) << 3);

    for (int i = 0; i < sizeof(array) / sizeof(int); i++)
        tree.insert(array + i);

    CPPUNIT_ASSERT(tree.size() == 7);
    for (int j = 1; j < 20; j++)
        CPPUNIT_ASSERT(!tree.lookup(&j));

    for (int j = 0; j < sizeof(array) / sizeof(int); j++)
        CPPUNIT_ASSERT(*tree.lookup(array + j) == array[j]);
}
