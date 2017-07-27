#include <gtest/gtest.h>
#include "andBoolExpr.h"
#include "boolTable.h"
#include "notBoolExpr.h"
#include "orBoolExpr.h"
#include "simpleExpr.h"

class BoolExprTest : public ::testing::Test {
protected:
    virtual void SetUp() {}

    virtual void TearDown() {
        // Code here will be called immediately after each test
        // (right before the destructor)
    }
};

TEST_F(BoolExprTest, simpleBool) {
    DP::SimpleExpr simple1("toto", "Boolean expression toto");
    ASSERT_TRUE(simple1());
    DP::NotBoolExpr nt(&simple1);
    ASSERT_FALSE(nt());
    DP::SimpleExpr simple2("titi", "Another boolean expression titi");
    DP::AndBoolExpr and1(&nt, &simple2);
    ASSERT_FALSE(and1());
    DP::OrBoolExpr or1(&nt, &simple2);
    ASSERT_TRUE(or1());
    DP::BoolTable table;
    or1.solve(table);
    std::string tb = table.getString();
    ASSERT_EQ(std::string("toto() ; titi() ; \n\n 0 0 : 1\n 1 0 : 0\n 0 1 : 1\n 1 1 : 1\n\n"), tb);
    and1.solve(table);
    tb = table.getString();
    ASSERT_EQ(std::string("toto() ; titi() ; \n\n 0 0 : 0\n 1 0 : 0\n 0 1 : 1\n 1 1 : 0\n\n"), tb);
}

TEST_F(BoolExprTest, sameSimpleExprMultiple) {
{
    DP::SimpleExpr simple1("toto", "Simple Expression to find multiple times");
    DP::SimpleExpr simple2("toto", "Simple Expression repeated a second time");
    DP::AndBoolExpr and1(&simple1, &simple2);
    DP::BoolTable table;
    and1.solve(table);
    std::string tb = table.getString();
    ASSERT_EQ(std::string("toto() ; \n\n 0 : 0\n 1 : 1\n\n"), tb);
}
};
