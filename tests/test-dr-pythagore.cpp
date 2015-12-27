#include <iostream>
#include "lexer.h"
#include "test-dr-pythagore.h"

static int OK = 0;
static int NOK = 0;

void inc_ok()
{
    OK++;
}

void inc_nok()
{
    NOK++;
}

using namespace std;

static void summary()
{
    cout << endl << "\x1b[31;1m" << NOK << "\x1b[0m / \x1b[32;1m"
         << OK + NOK << "\x1b[0m tests failed." << endl;
}

int main()
{
    DPLexer lexer;

    lexer.parse("Let B:Point");
    lexer.parse("Let A:Point");
    lexer.parse("Let (CD):Line");
    lexer.parse("Let (AB):Line");
    lexer.parse("A = B ?");
    ASSERT(!lexer.getResult());
    lexer.parse("A = A ?");
    ASSERT(lexer.getResult());
    lexer.parse("Assume C In (AB)");
    lexer.parse("C In (AB) ?");
    ASSERT(lexer.getResult());
    lexer.parse("Assume C != B");
    lexer.parse("A In (BC) ?");
    ASSERT(lexer.getResult());
    lexer.parse("Let D:Point");
    lexer.parse("D In (BC) ?");
    ASSERT(!lexer.getResult());
    lexer.parse("Assume A != D");
    lexer.parse("(BC) = (AD) ?");
    ASSERT(!lexer.getResult());
    lexer.parse("(BA) = (BC) ?");
    ASSERT(lexer.getResult());
    lexer.parse("Let [RG]: Segment");
    lexer.parse("[AB] = [BC] ?");
    ASSERT(!lexer.getResult());
    lexer.parse("[AB] = [BA] ?");
    ASSERT(lexer.getResult());
    lexer.parse("[AB] = [AB] ?");
    ASSERT(lexer.getResult());

    finalize();
    return 0;
}

void finalize()
{
    summary();
    exit(NOK);
}
