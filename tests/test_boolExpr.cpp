#include "simpleExpr.h"
#include "notBoolExpr.h"
#include "andBoolExpr.h"
#include "orBoolExpr.h"
#include "test_boolExpr.h"
#include "boolTable.h"

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
    DP::BoolTable table;
    or1.solve(table);
    std::string tb = table.getString();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Check table from the solve method with or",
                                 std::string("toto() ; titi() ; \n\n 0 0 : 1\n 1 0 : 0\n 0 1 : 1\n 1 1 : 1\n\n"), tb);
    and1.solve(table);
    tb = table.getString();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Check table from the solve method with and",
                                 std::string("toto() ; titi() ; \n\n 0 0 : 0\n 1 0 : 0\n 0 1 : 1\n 1 1 : 0\n\n"), tb);

}
