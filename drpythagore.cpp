#include <iostream>
#include "dplexer.h"

using namespace std;

int main()
{
    DPLexer lexer;

    lexer.parse("Let B:Point");
    lexer.parse("Let A:Point");
    return 0;
}
