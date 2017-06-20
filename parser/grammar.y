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
#include <sstream>
#include <iostream>
#include "grammar-prot.h"
#include "point.h"
#include "line.h"
#include "segment.h"

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
    cout << "A new point " << A->getName() << endl;
}
program ::= line(A) END.    {
    cout << "A new line " << A->getName() << endl;
}

program ::= boolean(A) END. {
    token->setResult(A);
}

/* Points in set */
boolean(A) ::= point(B) IN set(C) INTERRO. {
    cout << "Check if the point " << B->getName() << " is in " << C->getName() << endl;
    A = C->contains(B);
}

/* Distinct */
boolean(A) ::= point(B) DISTINCT point(C) INTERRO. {
    cout << "Check points equality" << endl;
    if (!B || !C) {
        cout << "syntax error: one of these points does not exist" << endl;
        token->setError();
    }
    else
        A = (*B != *C);
}

boolean(A) ::= line(B) DISTINCT line(C) INTERRO. {
    cout << "Check if " << B->getName() << " distinct " << C->getName() << endl;
    cout << "NOT IMPLEMENTED" << endl;
    A = false;
}

boolean(A) ::= segment(B) DISTINCT segment(C) INTERRO. {
    cout << "Check if " << B->getName() << " distinct " << C->getName() << endl;
    A = (*B != *C);
}

/* Equivalences */
boolean(A) ::= point(B) EQUALS point(C) INTERRO. {
    cout << "Check points equality" << endl;
    if (!B || !C) {
        cout << "syntax error: one of these points does not exist" << endl;
        token->setError();
    }
    else
        A = (*B == *C);
}

boolean(A) ::= line(B) PARALLEL line(C) INTERRO. {
    cout << "Check if lines " << B->getName() << " and " << C->getName() << " are parallel" << endl;
    A = B->parallelTo(*C);
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
        A = token->getPlan()->getLine(B, C);
        if (!A) {
            cout << "Error: " << B->getName() << " and " << C->getName() << " are not distinct to make a line" << endl;
            token->setError();
        }
    }
}

segment(A) ::= LBRA point(B) point(C) RBRA. {
    if (!B || !C) {
        cout << "syntax error (segment): one of those points does not exist" << endl;
        cout << "First point " << (B ? B->getName(): "No name") << endl;
        cout << "Second point " << (C ? C->getName(): "No name") << endl;
        token->setError();
    }
    else {
        A = token->getPlan()->getSegment(B, C);
        if (!A) {
            cout << "Error: " << B->getName() << " and " << C->getName() << " are not distinct to make a segment" << endl;
            token->setError();
        }
    }
}

point(A) ::= IDENT(B). {
    A = token->getPlan()->getPoint(B);
    if (!A) {
        cout << "Error: The point " << B << " is not recognized." << endl;
        token->setError();
    }
}

/* Constraints */
program ::= ASSUME point(A) IN set(B) END. {
    cout << "Assume " << A->getName() << " is in " << B->getName() << endl;
    B->addPoint(A);
}

program ::= ASSUME point(A) DISTINCT point(B) END. {
    stringstream ss;
    ss << A->getName() << " and " << B->getName() << " are assumed to be distinct";
    token->getPlan()->setRelation(BIN_REL_DISTINCT, A, B, ss.str());
}

program ::= ASSUME point(A) EQUALS point(B) END. {
    stringstream ss;
    ss << A->getName() << " and " << B->getName() << " are assumed equal";
    token->getPlan()->setRelation(BIN_REL_EQUALS, A, B, ss.str());
}

program ::= ASSUME line(A) PARALLEL line(B) END. {
    stringstream ss;
    ss << A->getName() << " is assumed parallel to " << B->getName();
    token->getPlan()->setRelation(BIN_REL_PARALLEL, A, B, ss.str());
}

program ::= ASSUME point(A) VIRG point(B) VIRG point(C) ALIGNED END. {
    stringstream ss;
    ss << A->getName() << ", " << B->getName() << " and " << C->getName() << " are aligned";
    token->getPlan()->setRelation(BIN_REL_ALIGNED, A, B, C, ss.str());
}

/* Definitions */
program ::= LET IDENT(A) COLON POINT END. {
    cout << "Let " << A << " be a point." << endl;
    DPPoint *a = new DPPoint(token->getPlan(), A);
}

program ::= LET LBRA IDENT(A) IDENT(B) RBRA COLON SEGMENT END. {
    cout << "Let [" << A << B << "] be a segment." << endl;
    DPSegment *a = new DPSegment(token->getPlan(), A, B);
}

program ::= LET LPAR IDENT(A) IDENT(B) RPAR COLON LINE END. {
    stringstream ss;
    ss << '(' << A << B << ") is a line.";
    DPLine *a = new DPLine(token->getPlan(), A, B);
}

