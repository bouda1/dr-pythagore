%name dPParse
%token_prefix CALC_TOKEN_

%token_type {char *}
%token_destructor { free $$; }

%type boolean { int }
%type point {DPPoint *}
%type line {DPLine *}

%extra_argument { DPParserToken *token }

%left PLUS MINUS.

%include {
#include <assert.h>
#include <iostream>
#include "grammar-prot.h"
#include "dppoint.h"
#include "dpline.h"

using namespace std;
}

%syntax_error {
    std::cout << "syntax error - ";
    int n = sizeof(yyTokenName) / sizeof(yyTokenName[0]);
    for (int i = 0; i < n; ++i) {
        int a = yy_find_shift_action(yypParser, (YYCODETYPE)i);
        if (a < YYNSTATE + YYNRULE) {
            std::cout << "expected " << yyTokenName[i] << std::endl;
        }
    }
}

%start_symbol program

/*calc ::= exp(e) END.                { std::cout << "= " << e << std::endl; }
   
exp(lhs) ::= NUMBER(e).             { lhs = e; }
exp(lhs) ::= LPAR exp(e) RPAR.      { lhs = e; }
exp(lhs) ::= exp(le) MINUS exp(re). { lhs = le - re; }

exp(lhs) ::= exp(le) PLUS exp(re).  { lhs = le + re; }
*/
program ::= point(A) END.   {
    cout << "Cool a point !" << endl;
    token->setElement(A);
}
program ::= line(A) END.    {
    cout << "Cool a line !" << endl;
    token->setElement(A);
}

program ::= boolean(A) END. {
    cout << "This is a boolean: " << A << endl;
}

boolean(A) ::= point(B) EQUALS point(C) INTERRO. {
    cout << "Check points equality" << endl;
    if (!B || !C)
        cout << "syntax error: one of those points does not exist" << endl;

    A = (*B == *C);
}

boolean(A) ::= line PARALLEL line INTERRO. {
    cout << "Check if lines are parallel" << endl;
    A = 0;
}

boolean(A) ::= point(B) IN line(C) INTERRO. {
    cout << "Check if the point " << B->getName() << " is in " << C->getName() << endl;
    A = C->contains(B);
}

line(A) ::= LPAR point(B) point(C) RPAR. {
    if (!B || !C)
        cout << "syntax error: one of those points does not exist" << endl;

    A = token->getPlan().getLine(B, C);
}

program ::= LET LPAR IDENT(A) IDENT(B) RPAR COLON LINE END. {

    cout << "Let (" << A << B << ") be a line." << endl;
    DPLine *a = new DPLine(token->getPlan(), A, B);
}

point(A) ::= IDENT(B). {
    A = token->getPlan().getPoint(B);
}

program ::= ASSUME point(A) IN line(B) END. {
    cout << "Assume a point " << A->getName() << endl;
    cout << "Assume " << A->getName() << " is in the line " << B->getName() << endl;
    B->addPoint(A);
}

program ::= LET IDENT(A) COLON POINT END. {
    cout << "Let " << A << " be a point." << endl;
    DPPoint *a = new DPPoint(token->getPlan(), A);
}
