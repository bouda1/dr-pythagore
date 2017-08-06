/* Dr-Pythagore
 * Copyright (C) 2016-2017 D. Boucher
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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

%left OR.
%left AND.
%left COLON.
%left VIRG IN.

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
#include "notBoolExpr.h"
#include "orBoolExpr.h"
#include "andBoolExpr.h"

using namespace std;
using namespace DP;

static const char *yellow = "\x1b[33;1m";
static const char *reset = "\x1b[0m";

}

%syntax_error {
    cout << "syntax error - ";
#ifndef NDEBUG
    int n = sizeof(yyTokenName) / sizeof(yyTokenName[0]);
    for (int i = 0; i < n; ++i) {
        int a = yy_find_shift_action(yypParser, (YYCODETYPE)i);
        if (a < YYNSTATE + YYNRULE) {
            std::cout << "expected " << yyTokenName[i] << std::endl;
        }
    }
#endif
    dPParseFinalize(yypParser);
}

%start_symbol program

/* Automatic translations */

point(A) ::= IDENT(B). {
    A = token->getPlane()->getPoint(B);
    if (!A) {
        cout << "Error: The point " << B << " is not recognized." << endl;
        token->setError(true);
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
        Point *a = new Point(token->getPlane(), s.c_str());
        cout << "Let " << s << " be a point." << endl;
    }
}

program ::= LET LBRA IDENT(A) IDENT(B) RBRA COLON SEGMENT END. {
    cout << "Let [" << A << B << "] be a segment." << endl;
    Segment *a = new Segment(token->getPlane(), A, B);
}

program ::= LET LPAR IDENT(A) IDENT(B) RPAR COLON LINE END. {
    stringstream ss;
    ss << '(' << A << B << ") is a line.";
    Line *a = new Line(token->getPlane(), A, B);
}

program ::= line(A) END. {
    cout << "A new line " << A->getName() << endl;
}

program ::= question(A) END. {
    token->setResult(A);
}

/* Points in set */
question(A) ::= point(B) IN set(C) INTERRO. {
    cout << yellow << "Check if the point " << B->getName() << " is in " << C->getName() << reset << endl;
    A = C->contains(B);
}

/* Distinct */
question(A) ::= point(B) DISTINCT point(C) INTERRO. {
    cout << yellow << "Check points equality" << reset << endl;
    if (!B || !C) {
        cout << "syntax error: one of these points does not exist" << endl;
        token->setError(true);
        A = false;
    }
    else
        A = (*B != *C);
}

question(A) ::= line(B) DISTINCT line(C) INTERRO. {
    cout << yellow << "Check if " << B->getName() << " distinct " << C->getName() << reset << endl;
    cout << "NOT IMPLEMENTED" << endl;
    A = false;
}

question(A) ::= segment(B) DISTINCT segment(C) INTERRO. {
    cout << yellow << "Check if " << B->getName() << " distinct " << C->getName() << reset << endl;
    A = (*B != *C);
}

/* Equivalences */
question(A) ::= point(B) EQUALS point(C) INTERRO. {
    cout << yellow << "Check points equality" << reset << endl;
    if (!B || !C) {
        cout << "syntax error: one of these points does not exist" << endl;
        token->setError(true);
        A = false;
    }
    else
        A = (*B == *C);
}

question(A) ::= line(B) PARALLEL line(C) INTERRO. {
    cout << yellow << "Check if lines " << B->getName() << " and " << C->getName() << " are parallel" << reset << endl;
    A = B->parallelTo(*C);
}

question(A) ::= line(B) EQUALS line(C) INTERRO. {
    if (!B || !C) {
        token->setError(true);
        A = false;
    }
    else {
        cout << yellow << "Check if lines " << B->getName()
             << " and " << C->getName() << " are equal" << reset << endl;
        A = (*B == *C);
    }
}

question(A) ::= segment(B) EQUALS segment(C) INTERRO. {
    if (!B || !C) {
        token->setError(true);
        A = false;
    }
    else {
        cout << yellow << "Check if segments " << B->getName()
             << " and " << C->getName() << " are equal " << reset << endl;
        A = (*B == *C);
    }
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
        token->setError(true);
        A = nullptr;
    }
    else {
        A = token->getPlane()->getLine(B, C);
        if (!A) {
            cout << "Error: " << B->getName() << " and " << C->getName() << " are not distinct to make a line" << endl;
            token->setError(true);
        }
    }
}

segment(A) ::= LBRA point(B) point(C) RBRA. {
    if (!B || !C) {
        cout << "syntax error (segment): one of those points does not exist" << endl;
        cout << "First point " << (B ? B->getName(): "No name") << endl;
        cout << "Second point " << (C ? C->getName(): "No name") << endl;
        token->setError(true);
        A = nullptr;
    }
    else {
        A = token->getPlane()->getSegment(B, C);
        if (!A) {
            cout << "Error: " << B->getName() << " and " << C->getName() << " are not distinct to make a segment" << endl;
            token->setError(true);
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
    E = new NotBoolExpr(simp, ss.str());
}

expr(E) ::= point(A) IN set(B). {
    stringstream ss;
    ss << A->getName() << " is in " << B->getName();
    std::cout << "EXPRESSION " << ss.str() << std::endl;
    E = new SimpleExpr("Element", A, B, ss.str());
}

expr(E) ::= expr(A) AND expr(B). {
    stringstream ss;
    ss << A->getDescr() << " and " << B->getDescr();
    std::cout << "EXPRESSION " << ss.str() << std::endl;
    E = new AndBoolExpr(A, B, ss.str());
}
expr(E) ::= expr(A) OR expr(B). {
    stringstream ss;
    ss << A->getDescr() << " or " << B->getDescr();
    std::cout << "EXPRESSION " << ss.str() << std::endl;
    E = new OrBoolExpr(A, B, ss.str());
}

/* Rules */
program ::= RULE COLON expr(E) IMPLIES expr(F) END. {
    cout << "New rule definition " << E->getString() << " => " << F->getString() << endl;
    token->getPlane()->addRule(E, F);
}

program ::= ASSUME expr(E) END. {
    cout << "Assume " << E->getString() << endl;
    token->getPlane()->addExpression(E);
}
