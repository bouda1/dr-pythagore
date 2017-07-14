#include <iostream>
#include <cstring>
#include <malloc.h>
#include "lexer.h"
#include "grammar.h"

using namespace std;
using namespace DP;

Lexer::Lexer(Plane *plan)
    : _content(0), _plane(plan), _token(_plane), _start(0), _limit(0)
{
    _parser = dPParseAlloc(malloc);
}

Lexer::~Lexer()
{
    dPParseFree(_parser, free);
}

char *Lexer::getTokenValue()
{
    return strndup(_start, _cursor - _start);
}

void Lexer::debug(int a, char b)
{
    cout << "DEBUG " << a << " ; " << b << endl;
    cout << "_start = " << _start << endl;
}

int Lexer::scan()
{
    _start = _cursor;
#define YYCTYPE char
#define YYCURSOR _cursor
#define YYLIMIT _limit
#define YYMARKER _marker
#define YYCTXMARKER _ctxmarker
#define YYFILL(n)
#define YYDEBUG(a,b) debug(a, b)

cont:
    /*!re2c
        re2c:yyfill:enable = 0;

        "\000"              { return CALC_TOKEN_END; }
        "Let"               { return CALC_TOKEN_LET; }
        "Point"             { return CALC_TOKEN_POINT; }
        "Line"              { return CALC_TOKEN_LINE; }
        "Segment"           { return CALC_TOKEN_SEGMENT; }
        "Assume"            { return CALC_TOKEN_ASSUME; }
        "In"                { return CALC_TOKEN_IN; }
        "Not"               { return CALC_TOKEN_NOT; }
        "Aligned"           { return CALC_TOKEN_ALIGNED; }
        ","                 { return CALC_TOKEN_VIRG; }
        [A-Za-z]            { return CALC_TOKEN_IDENT; }
        "("                 { return CALC_TOKEN_LPAR; }
        "["                 { return CALC_TOKEN_LBRA; }
        ")"                 { return CALC_TOKEN_RPAR; }
        "]"                 { return CALC_TOKEN_RBRA; }
        ":"                 { return CALC_TOKEN_COLON; }
        "="                 { return CALC_TOKEN_EQUALS; }
        "?"                 { return CALC_TOKEN_INTERRO; }
        "//"                { return CALC_TOKEN_PARALLEL; }
        "!="                { return CALC_TOKEN_DISTINCT; }
        "=>"                { return CALC_TOKEN_IMPLIES; }
        "Rule"              { return CALC_TOKEN_RULE; }
        " "                 { _start++; goto cont; }
    */
}

void Lexer::parse(const char *s)
{
    //FILE *f = fopen("/tmp/parser.dbr", "a");
    //dPParseTrace(f, "DP => ");
    char *word;
    int op_token;
    _content = s;
    _start = _cursor = _content;
    _limit = _content + strlen(_content);

    do {
        op_token = scan();
        word = getTokenValue();
        dPParse(_parser, op_token, word, &_token);
    }
    while (!_token.onError() && op_token != CALC_TOKEN_END);

    if (!_token.onError())
        dPParse(_parser, 0, NULL, &_token);
    else
        _token.setResult(false);
}

bool Lexer::getResult() const
{
    return _token.getResult();
}

string Lexer::getLastContradiction() const
{
    return _plane->getLastContradiction();
}
