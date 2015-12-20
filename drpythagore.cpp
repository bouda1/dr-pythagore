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
    lexer.parse("Assume C != B");
    lexer.parse("A In (BC) ?");
    lexer.parse("Let D:Point");
    lexer.parse("D In (BC) ?");
    lexer.parse("Assume A != D");
    lexer.parse("(BC) = (AD) ?");
    lexer.parse("(BA) = (BC) ?");
    lexer.parse("Let [RG]: Segment");
    lexer.parse("[AB] = [BC] ?");
    lexer.parse("[AB] = [BA] ?");
    lexer.parse("[AB] = [AB] ?");
    return 0;
}
