#include <unistd.h>
#include <string>
#include "lexer.h"
#include "test_task_checkequaldistinct.h"

using namespace std;

void TestTaskCheckEqualDistinct::setUp()
{
    _plan = new DPPlane;
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
    _lexer->parse("Assume A!=B");
    sleep(1);
    string str = _lexer->getLastContradiction();
    cout << "STR: " << str << endl;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Cannot assume A=B and A!=B", str, string("<< A and B are assumed equal >> not compatible with << A and B are assumed to be distinct >>"));
}

