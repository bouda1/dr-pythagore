#include "lexer.h"
#include "test_lexer.h"

void TestDPLexer::setUp()
{
    _plan = new DP::Plane;
    _lexer = new DP::Lexer(_plan);
}

void TestDPLexer::tearDown()
{
    delete _lexer;
}

void TestDPLexer::testEquality1()
{
    _lexer->parse("Let B:Point");
    _lexer->parse("Let A:Point");
    _lexer->parse("Let (CD):Line");
    _lexer->parse("Let (AB):Line");
    _lexer->parse("A = B ?");
    CPPUNIT_ASSERT(!_lexer->getResult());
    _lexer->parse("A = A ?");
    CPPUNIT_ASSERT(_lexer->getResult());
}

void TestDPLexer::testEquality2()
{
    _lexer->parse("Let (AB):Line");
    _lexer->parse("Let (CD):Line");
    _lexer->parse("Let W:Point");
    _lexer->parse("Let X:Point");
    _lexer->parse("Assume W!=X");
    _lexer->parse("W = X ?");
    CPPUNIT_ASSERT(!_lexer->getResult());
    _lexer->parse("W != X ?");
    CPPUNIT_ASSERT(_lexer->getResult());
    _lexer->parse("Assume C In (AB)");
    _lexer->parse("C In (AB) ?");
    CPPUNIT_ASSERT(_lexer->getResult());
    _lexer->parse("Assume C != B");
    _lexer->parse("A In (BC) ?");
    CPPUNIT_ASSERT(_lexer->getResult());
    _lexer->parse("Let D:Point");
    _lexer->parse("D In (BC) ?");
    CPPUNIT_ASSERT(!_lexer->getResult());
    _lexer->parse("Assume A != D");
    _lexer->parse("(BC) = (AD) ?");
    CPPUNIT_ASSERT(!_lexer->getResult());
    _lexer->parse("(BA) = (BC) ?");
    CPPUNIT_ASSERT(_lexer->getResult());
    _lexer->parse("Let [RG]: Segment");
    _lexer->parse("[AB] = [BC] ?");
    CPPUNIT_ASSERT(!_lexer->getResult());
    _lexer->parse("[AB] = [BA] ?");
    CPPUNIT_ASSERT(_lexer->getResult());
    _lexer->parse("[AB] = [AB] ?");
    CPPUNIT_ASSERT(_lexer->getResult());
    _lexer->parse("Let [FG]:Segment");
    _lexer->parse("Let [HJ]:Segment");
    _lexer->parse("[FG] = [HJ] ?");
    CPPUNIT_ASSERT(!_lexer->getResult());
}

