%name dPParse
%token_prefix CALC_TOKEN_

%token_type {char *}
%token_destructor { free $$; }

%type expr {BoolExpr *}
%type question { int }
%type point {Point *}
%type line {Line *}
%type segment {Segment *}
%type set {Set *}
%type list {list<string> *}

%extra_argument { ParserToken *token }

%left COLON.
%left VIRG.

%include {
#include <cassert>
#include <sstream>
#include <iostream>
#include <list>
#include "grammar-prot.h"
#include "point.h"
#include "line.h"
#include "segment.h"
#include "simpleExpr.h"
#include "treeBoolExpr.h"

using namespace std;
using namespace DP;
}

%syntax_error {
    cout << "syntax error - ";
    int n = sizeof(yyTokenName) / sizeof(yyTokenName[0]);
    for (int i = 0; i < n; ++i) {
        int a = yy_find_shift_action(yypParser, (YYCODETYPE)i);
        if (a < YYNSTATE + YYNRULE) {
            std::cout << "expected " << yyTokenName[i] << std::endl;
        }
    }
}

%start_symbol program

/* Automatic translations */

point(A) ::= IDENT(B). {
    A = token->getPlan()->getPoint(B);
    if (!A) {
        cout << "Error: The point " << B << " is not recognized." << endl;
        token->setError();
    }
}

list(L) ::= IDENT(A). {
    cout << "Ho ! This is a list" << endl;
    L = new list<string>();
    L->push_back(A);
}

list(L) ::= list(A) VIRG IDENT(B). {
    cout << "The list is growing up!" << endl;
    L = A;
    L->push_back(B);
}

/* Definitions */
program ::= LET list(A) COLON POINT END. {
    cout << "Points definition" << endl;
    for (string s : *A) {
        Point *a = new Point(token->getPlan(), s.c_str());
        cout << "Let " << s << " be a point." << endl;
    }
}

program ::= LET LBRA IDENT(A) IDENT(B) RBRA COLON SEGMENT END. {
    cout << "Let [" << A << B << "] be a segment." << endl;
    Segment *a = new Segment(token->getPlan(), A, B);
}

program ::= LET LPAR IDENT(A) IDENT(B) RPAR COLON LINE END. {
    stringstream ss;
    ss << '(' << A << B << ") is a line.";
    Line *a = new Line(token->getPlan(), A, B);
}

program ::= line(A) END.    {
    cout << "A new line " << A->getName() << endl;
}

program ::= question(A) END. {
    token->setResult(A);
}

/* Points in set */
question(A) ::= point(B) IN set(C) INTERRO. {
    cout << "Check if the point " << B->getName() << " is in " << C->getName() << endl;
    A = C->contains(B);
}

/* Distinct */
question(A) ::= point(B) DISTINCT point(C) INTERRO. {
    cout << "Check points equality" << endl;
    if (!B || !C) {
        cout << "syntax error: one of these points does not exist" << endl;
        token->setError();
    }
    else
        A = (*B != *C);
}

question(A) ::= line(B) DISTINCT line(C) INTERRO. {
    cout << "Check if " << B->getName() << " distinct " << C->getName() << endl;
    cout << "NOT IMPLEMENTED" << endl;
    A = false;
}

question(A) ::= segment(B) DISTINCT segment(C) INTERRO. {
    cout << "Check if " << B->getName() << " distinct " << C->getName() << endl;
    A = (*B != *C);
}

/* Equivalences */
question(A) ::= point(B) EQUALS point(C) INTERRO. {
    cout << "Check points equality" << endl;
    if (!B || !C) {
        cout << "syntax error: one of these points does not exist" << endl;
        token->setError();
    }
    else
        A = (*B == *C);
}

question(A) ::= line(B) PARALLEL line(C) INTERRO. {
    cout << "Check if lines " << B->getName() << " and " << C->getName() << " are parallel" << endl;
    A = B->parallelTo(*C);
}

question(A) ::= line(B) EQUALS line(C) INTERRO. {
    cout << "Check if " << B->getName() << " equals " << C->getName() << endl;
    A = (*B == *C);
}

question(A) ::= segment(B) EQUALS segment(C) INTERRO. {
    cout << "Check if " << B->getName() << " equals " << C->getName() << endl;
    A = (*B == *C);
}

/* Getters */
set(A) ::= line(B). {
    A = static_cast<Set *>(B);
}

set(A) ::= segment(B). {
    A = static_cast<Set *>(B);
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

expr(E) ::= point(A) DISTINCT point(B). {
    stringstream ss;
    ss << A->getName() << " is distinct of " << B->getName();
    E = new SimpleExpr("Distinct", A, B, ss.str());
}

expr(E) ::= point(A) EQUALS point(B). {
    stringstream ss;
    ss << A->getName() << " is equal to " << B->getName();
    E = new SimpleExpr("Equals", A, B, ss.str());
}

expr(E) ::= line(A) PARALLEL line(B). {
    stringstream ss;
    ss << A->getName() << " is parallel to " << B->getName();
    E = new SimpleExpr("Parallel", A, B, ss.str());
}

expr(E) ::= point(A) VIRG point(B) VIRG point(C) ALIGNED. {
    stringstream ss;
    ss << A->getName() << ", " << B->getName() << ", " << C->getName() << " are aligned";
    E = new SimpleExpr("Aligned", A, B, C, ss.str());
}

expr(E) ::= point(A) VIRG point(B) VIRG point(C) NOT ALIGNED. {
    stringstream ss;
    ss << A->getName() << ", " << B->getName() << ", " << C->getName() << " are aligned";
    SimpleExpr *simp = new SimpleExpr("Aligned", A, B, C, ss.str());
    E = new TreeBoolExpr("Not", simp, ss.str());
}

/* Constraints */
program ::= ASSUME point(A) IN set(B) END. {
    cout << "Assume " << A->getName() << " is in " << B->getName() << endl;
    B->addPoint(A);
}

program ::= ASSUME expr(E) END. {
    cout << "Assume " << E->getString() << endl;
    token->getPlan()->addExpression(E);
}

//program ::= ASSUME point(A) DISTINCT point(B) END. {
//    stringstream ss;
//    ss << A->getName() << " and " << B->getName() << " are assumed to be distinct";
//    token->getPlan()->setRelation(OP_REL_DISTINCT, A, B, ss.str());
//}

//program ::= ASSUME point(A) EQUALS point(B) END. {
//    stringstream ss;
//    ss << A->getName() << " and " << B->getName() << " are assumed equal";
//    token->getPlan()->setRelation(OP_REL_EQUALS, A, B, ss.str());
//}

//program ::= ASSUME line(A) PARALLEL line(B) END. {
//    stringstream ss;
//    ss << A->getName() << " is assumed parallel to " << B->getName();
//    token->getPlan()->setRelation(OP_REL_PARALLEL, A, B, ss.str());
//}

//program ::= ASSUME point(A) VIRG point(B) VIRG point(C) ALIGNED END. {
//    stringstream ss;
//    ss << A->getName() << ", " << B->getName() << " and " << C->getName() << " are aligned";
//    token->getPlan()->setRelation(OP_REL_ALIGNED, A, B, C, ss.str());
//}

//program ::= ASSUME point(A) VIRG point(B) VIRG point(C) NOT ALIGNED END. {
//    stringstream ss;
//    ss << A->getName() << ", " << B->getName() << " and " << C->getName() << " are not aligned";
//    token->getPlan()->setRelation(OP_REL_NOTALIGNED, A, B, C, ss.str());
//}

