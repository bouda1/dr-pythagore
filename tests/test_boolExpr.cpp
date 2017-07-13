#include "simpleExpr.h"
#include "treeBoolExpr.h"
#include "test_boolExpr.h"

void TestDPBoolExpr::setUp()
{
}

void TestDPBoolExpr::tearDown()
{
}

void TestDPBoolExpr::testSimpleBool()
{
    DP::SimpleExpr simple("toto", "Boolean expression toto");
    CPPUNIT_ASSERT(simple());
    DP::TreeBoolExpr nt("Not", &simple);
    CPPUNIT_ASSERT(!nt());
}

//void TestDPLexer::testEquality2()
//{
//    _lexer->parse("Let (AB):Line");
//    _lexer->parse("Let (CD):Line");
//    _lexer->parse("Let W:Point");
//    _lexer->parse("Let X:Point");
//    _lexer->parse("Assume W!=X");
//    _lexer->parse("W = X ?");
//    CPPUNIT_ASSERT(!_lexer->getResult());
//    _lexer->parse("W != X ?");
//    CPPUNIT_ASSERT(_lexer->getResult());
//    _lexer->parse("Assume C In (AB)");
//    _lexer->parse("C In (AB) ?");
//    CPPUNIT_ASSERT(_lexer->getResult());
//    _lexer->parse("Assume C != B");
//    _lexer->parse("A In (BC) ?");
//    CPPUNIT_ASSERT(_lexer->getResult());
//    _lexer->parse("Let D:Point");
//    _lexer->parse("D In (BC) ?");
//    CPPUNIT_ASSERT(!_lexer->getResult());
//    _lexer->parse("Assume A != D");
//    _lexer->parse("(BC) = (AD) ?");
//    CPPUNIT_ASSERT(!_lexer->getResult());
//    _lexer->parse("(BA) = (BC) ?");
//    CPPUNIT_ASSERT(_lexer->getResult());
//    _lexer->parse("Let [RG]: Segment");
//    _lexer->parse("[AB] = [BC] ?");
//    CPPUNIT_ASSERT(!_lexer->getResult());
//    _lexer->parse("[AB] = [BA] ?");
//    CPPUNIT_ASSERT(_lexer->getResult());
//    _lexer->parse("[AB] = [AB] ?");
//    CPPUNIT_ASSERT(_lexer->getResult());
//    _lexer->parse("Let [FG]:Segment");
//    _lexer->parse("Let [HJ]:Segment");
//    _lexer->parse("[FG] = [HJ] ?");
//    CPPUNIT_ASSERT(!_lexer->getResult());
//}
//
