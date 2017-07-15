#include "simpleExpr.h"
#include "notBoolExpr.h"
#include "andBoolExpr.h"
#include "orBoolExpr.h"
#include "test_boolExpr.h"

void TestDPBoolExpr::setUp()
{
}

void TestDPBoolExpr::tearDown()
{
}

void TestDPBoolExpr::testSimpleBool()
{
    DP::SimpleExpr simple1("toto", "Boolean expression toto");
    CPPUNIT_ASSERT(simple1());
    DP::NotBoolExpr nt(&simple1);
    CPPUNIT_ASSERT(!nt());
    DP::SimpleExpr simple2("titi", "Another boolean expression titi");
    DP::AndBoolExpr and1(&nt, &simple2);
    CPPUNIT_ASSERT(!and1());
    DP::OrBoolExpr or1(&nt, &simple2);
    CPPUNIT_ASSERT(or1());
}
