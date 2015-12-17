#include <iostream>
#include "dplexer.h"

using namespace std;

int main()
{
    DPLexer lexer;

    lexer.parse("Let B:Point");
    lexer.parse("Let A:Point");
    lexer.parse("Let (CD):Line");
    lexer.parse("Let (AB):Line");
    lexer.parse("A = B ?");
    lexer.parse("A = A ?");
    lexer.parse("Assume C In (AB)");
    lexer.parse("C In (AB) ?");
    return 0;
}
