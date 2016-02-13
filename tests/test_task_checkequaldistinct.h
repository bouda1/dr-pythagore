#ifndef __TEST_TASK_CHECKEQUALDISTINCT_H__
#define __TEST_TASK_CHECKEQUALDISTINCT_H__
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "plan.h"
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
    DPPlan *_plan;
    DPLexer *_lexer;
};

#endif /* __TEST_TASK_CHECKEQUALDISTINCT_H__ */
