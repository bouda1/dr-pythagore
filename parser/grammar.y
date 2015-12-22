%name dPParse
%token_prefix CALC_TOKEN_

%token_type {char *}
%token_destructor { free $$; }

%type boolean { int }
%type point {DPPoint *}
%type line {DPLine *}
%type segment {DPSegment *}
%type set {DPSet *}

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

/* Checks */
boolean(A) ::= point(B) EQUALS point(C) INTERRO. {
    cout << "Check points equality" << endl;
    if (!B || !C) {
        cout << "syntax error: one of those points does not exist" << endl;
        token->setError();
    }
    else
        A = (*B == *C);
}

/* Points in set */
boolean(A) ::= point(B) IN set(C) INTERRO. {
    cout << "Check if the point " << B->getName() << " is in " << C->getName() << endl;
    A = C->contains(B);
}

/* Equivalences */
boolean(A) ::= line PARALLEL line INTERRO. {
    cout << "Check if lines are parallel" << endl;
    A = 0;
}

boolean(A) ::= line(B) EQUALS line(C) INTERRO. {
    cout << "Check if " << B->getName() << " equals " << C->getName() << endl;
    A = (*B == *C);
}

boolean(A) ::= segment(B) EQUALS segment(C) INTERRO. {
    cout << "Check if " << B->getName() << " equals " << C->getName() << endl;
    A = (*B == *C);
}

/* Getters */
set(A) ::= line(B). {
    A = static_cast<DPSet *>(B);
}

set(A) ::= segment(B). {
    A = static_cast<DPSet *>(B);
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

point(A) ::= IDENT(B). {
    A = token->getPlan().getPoint(B);
}

/* Constraints */
program ::= ASSUME point(A) IN set(B) END. {
    cout << "Assume " << A->getName() << " is in " << B->getName() << endl;
    B->addPoint(A);
}

program ::= ASSUME point(A) DISTINCT point(B) END. {
    cout << "Assume " << A->getName() << " is distinct from " << B->getName() << endl;
    token->getPlan().setRelation(BIN_REL_DISTINCT, A, B);
}

/* Definitions */
program ::= LET IDENT(A) COLON POINT END. {
    cout << "Let " << A << " be a point." << endl;
    DPPoint *a = new DPPoint(token->getPlan(), A);
}

program ::= LET LBRA IDENT(A) IDENT(B) RBRA COLON SEGMENT END. {
    cout << "Let [" << A << B << "] be a segment." << endl;
}

program ::= LET LPAR IDENT(A) IDENT(B) RPAR COLON LINE END. {

    cout << "Let (" << A << B << ") be a line." << endl;
    DPLine *a = new DPLine(token->getPlan(), A, B);
}

