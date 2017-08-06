#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "lexer.h"

class LexerTest : public ::testing::Test {
protected:
    DP::Plane *_plan;
    DP::Lexer *_lexer;

    virtual void SetUp() {
        _plan = new DP::Plane;
        _lexer = new DP::Lexer(_plan);
    }

    virtual void TearDown() {
        delete _lexer;
    }
};

TEST_F(LexerTest, testEquality1) {
    _lexer->parse("Let B:Point");
    _lexer->parse("Let A:Point");
    _lexer->parse("Let (CD):Line");
    _lexer->parse("Let (AB):Line");
    _lexer->parse("A = B ?");
    ASSERT_FALSE(_lexer->getResult());
    _lexer->parse("A = A ?");
    ASSERT_TRUE(_lexer->getResult());
}

TEST_F(LexerTest, testEquality2) {
    _lexer->parse("Let (AB):Line");
    _lexer->parse("Let (CD):Line");
    _lexer->parse("Let W:Point");
    _lexer->parse("Let X:Point");
    _lexer->parse("Assume W!=X");
    _lexer->parse("W = X ?");
    ASSERT_FALSE(_lexer->getResult());
    _lexer->parse("W != X ?");
    ASSERT_TRUE(_lexer->getResult());
    _lexer->parse("Assume C In (AB)");
    _lexer->parse("C In (AB) ?");
    ASSERT_TRUE(_lexer->getResult());
    _lexer->parse("Assume C != B");
    _lexer->parse("A In (BC) ?");
    ASSERT_TRUE(_lexer->getResult());
    _lexer->parse("Let D:Point");
    _lexer->parse("D In (BC) ?");
    ASSERT_FALSE(_lexer->getResult());
    _lexer->parse("Assume A != D");
    _lexer->parse("(BC) = (AD) ?");
    ASSERT_FALSE(_lexer->getResult());
    _lexer->parse("(BA) = (BC) ?");
    ASSERT_TRUE(_lexer->getResult());
    _lexer->parse("Let [RG]: Segment");
    _lexer->parse("[AB] = [BC] ?");
    ASSERT_FALSE(_lexer->getResult());
    _lexer->parse("[AB] = [BA] ?");
    ASSERT_TRUE(_lexer->getResult());
    _lexer->parse("[AB] = [AB] ?");
    ASSERT_TRUE(_lexer->getResult());
    _lexer->parse("Let [FG]:Segment");
    _lexer->parse("Let [HJ]:Segment");
    _lexer->parse("[FG] = [HJ] ?");
    ASSERT_FALSE(_lexer->getResult());
}

TEST_F(LexerTest, testAssumeWithOr) {
    _lexer->parse("Let A:Point");
    _lexer->parse("Let (FG):Line");
    _lexer->parse("Let (HJ):Line");
    _lexer->parse("Assume A In (FG) Or A In (HJ)");
    _lexer->parse("A In (FG) ?");
    ASSERT_FALSE(_lexer->getResult());
}

TEST_F(LexerTest, testAssumeWithAnd) {
    _lexer->parse("Let A:Point");
    _lexer->parse("Let (FG):Line");
    _lexer->parse("Let (HJ):Line");
    _lexer->parse("Assume A In (FG) And A In (HJ)");
    _lexer->parse("A In (FG) ?");
    ASSERT_TRUE(_lexer->getResult());
}

TEST_F(LexerTest, testLinesEqualityWithBadDefinition) {
    _lexer->parse("Let (AB):Line");
    _lexer->parse("Let (CD):Line");
    _lexer->parse("Let K:Point");
    _lexer->parse("Assume K In (AB)");
    _lexer->parse("(AB) = (KB) ?");
    ASSERT_FALSE(_lexer->getResult());
    _lexer->parse("Assume K != B");
    _lexer->parse("(AB) = (KB) ?");
    ASSERT_TRUE(_lexer->getResult());
}
