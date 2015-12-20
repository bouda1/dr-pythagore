%name dPParse
%token_prefix CALC_TOKEN_

%token_type {char *}
%token_destructor { free $$; }

%type boolean { int }
%type point {DPPoint *}
%type line {DPLine *}
%type segment {DPSegment *}

%extra_argument { DPParserToken *token }

%left PLUS MINUS.

%include {
#include <assert.h>
#include <iostream>
#include "grammar-prot.h"
#include "dppoint.h"
#include "dpline.h"
#include "dpsegment.h"

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
    if (!B || !C) {
        cout << "syntax error: one of those points does not exist" << endl;
        token->setError();
    }
    else
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

boolean(A) ::= line(B) EQUALS line(C) INTERRO. {
    cout << "Check if " << B->getName() << " equals " << C->getName() << endl;
    A = (*B == *C);
}

boolean(A) ::= segment(B) EQUALS segment(C) INTERRO. {
    cout << "Check if " << B->getName() << " equals " << C->getName() << endl;
    A = (*B == *C);
}

line(A) ::= LPAR point(B) point(C) RPAR. {
    if (!B || !C) {
        cout << "syntax error: one of those points does not exist" << endl;
        token->setError();
    }
    else {
        A = token->getPlan().getLine(B, C);
        if (!A) {
            cout << "Error: " << B->getName() << " and " << C->getName() << " are not distinct to make a line" << endl;
            token->setError();
        }
    }
}

segment(A) ::= LBRA point(B) point(C) RBRA. {
    if (!B || !C) {
        cout << "syntax error: one of those points does not exist" << endl;
        token->setError();
    }
    else {
        A = token->getPlan().getSegment(B, C);
        if (!A) {
            cout << "Error: " << B->getName() << " and " << C->getName() << " are not distinct to make a segment" << endl;
            token->setError();
        }
    }
}

program ::= LET LPAR IDENT(A) IDENT(B) RPAR COLON LINE END. {

    cout << "Let (" << A << B << ") be a line." << endl;
    DPLine *a = new DPLine(token->getPlan(), A, B);
}

program ::= LET LBRA IDENT(A) IDENT(B) RBRA COLON SEGMENT END. {
    cout << "Let [" << A << B << "] be a segment." << endl;
}

point(A) ::= IDENT(B). {
    A = token->getPlan().getPoint(B);
}

program ::= ASSUME point(A) IN line(B) END. {
    cout << "Assume " << A->getName() << " is in the line " << B->getName() << endl;
    B->addPoint(A);
}

program ::= ASSUME point(A) DISTINCT point(B) END. {
    cout << "Assume " << A->getName() << " is distinct from " << B->getName() << endl;
    token->getPlan().setRelation(BIN_REL_DISTINCT, A, B);
}

program ::= LET IDENT(A) COLON POINT END. {
    cout << "Let " << A << " be a point." << endl;
    DPPoint *a = new DPPoint(token->getPlan(), A);
}
