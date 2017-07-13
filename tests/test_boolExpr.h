#ifndef __TEST_BOOL_H__
#define __TEST_BOOL_H__
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestDPBoolExpr : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestDPBoolExpr);
    CPPUNIT_TEST(testSimpleBool);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void testSimpleBool();

};

#endif /* __TEST_BOOL_H__ */
