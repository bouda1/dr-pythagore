#include "lexer.h"
#include "test_task_checkequaldistinct.h"

void TestTaskCheckEqualDistinct::setUp()
{
    _plan = new DPPlan;
    _lexer = new DPLexer(_plan);
}

void TestTaskCheckEqualDistinct::tearDown()
{
    delete _lexer;
}

void TestTaskCheckEqualDistinct::testPoints()
{
    _lexer->parse("Let A:Point");
    _lexer->parse("Let B:Point");
    _lexer->parse("Assume A=B");
    _lexer->parse("A = B ?");
    CPPUNIT_ASSERT(_lexer->getResult());
//    _lexer->parse("Assume A!=B");
}
