#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include "test_lexer.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TestDPLexer);

int main(int argc, char **argv)
{
    CPPUNIT_NS::TestResult testResult;

    CPPUNIT_NS::TestResultCollector collectedResults;
    testResult.addListener(&collectedResults);

    CPPUNIT_NS::BriefTestProgressListener progress;
    testResult.addListener(&progress);

    CPPUNIT_NS::TestRunner runner;
    runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
    runner.run(testResult);

    CPPUNIT_NS::CompilerOutputter compilerOutputter(&collectedResults, std::cerr);
    compilerOutputter.write();
    return collectedResults.wasSuccessful() ? 0 : 1;
}

