#ifndef __TEST_DPTREE_H__
#define __TEST_DPTREE_H__
#include <vector>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "dptree.h"

class TestDPTree : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestDPTree);
    CPPUNIT_TEST(testTreeSize);
    CPPUNIT_TEST(testTreeInsert);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

    static int getBit(int *treeData, int range);
    static int compareData(int *treeData, int *userData,
                           int start, int end,
                           DPNodeContinue &cont);

protected:
    void testTreeSize();
    void testTreeInsert();

private:
};

#endif /* __TEST_DPTREE_H__ */
