#ifndef __TEST_TASK_CHECKEQUALDISTINCT_H__
#define __TEST_TASK_CHECKEQUALDISTINCT_H__
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "plane.h"
#include "lexer.h"

class TestTaskCheckEqualDistinct : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestTaskCheckEqualDistinct);
    CPPUNIT_TEST(testPoints);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void testPoints();

private:
    DP::Plane *_plan;
    DP::Lexer *_lexer;
};

#endif /* __TEST_TASK_CHECKEQUALDISTINCT_H__ */
