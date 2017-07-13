#ifndef __TEST_LEXER_H__
#define __TEST_LEXER_H__
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "plane.h"
#include "lexer.h"

class TestDPLexer : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestDPLexer);
    CPPUNIT_TEST(testEquality1);
    CPPUNIT_TEST(testEquality2);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void testEquality1();
    void testEquality2();

private:
    DP::Plane *_plan;
    DP::Lexer *_lexer;
};

#endif /* __TEST_LEXER_H__ */
