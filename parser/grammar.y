%name dPParse
%token_prefix CALC_TOKEN_

%token_type {char *}
/*%token_destructor { delete $$; } */

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
    cout << "A boolean: " << A << endl;
}

boolean(A) ::= IDENT(B) EQUALS IDENT(C). {
<<<<<<< 3dd2d18a20ffd36083b3860ea9a3f2fc93f88328
=======
    cout << "Check equality" << endl;
>>>>>>> BUG: parser: Fix a compilation difficulty. A first equality test added
    DPPoint *a = token->getPlan().getPoint(B);
    DPPoint *b = token->getPlan().getPoint(C);
    if (!a || !b)
        cout << "syntax error: one of those points does not exist" << endl;

    A = (*a == *b);
}

line(A) ::= LET LPAR IDENT(B) IDENT(C) RPAR COLON LINE. {
    A = new DPLine(token->getPlan(), B, C);
}

point(A) ::= LET IDENT(B) COLON POINT. {
    cout << "Oh ! a point..." << endl;
<<<<<<< 3dd2d18a20ffd36083b3860ea9a3f2fc93f88328
=======
    cout << "Its name is " << B << endl;
>>>>>>> BUG: parser: Fix a compilation difficulty. A first equality test added
    A = new DPPoint(token->getPlan(), B);
}
