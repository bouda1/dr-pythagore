#include <iostream>
#include <cstring>
#include <malloc.h>
#include "lexer.h"
#include "grammar.h"

using namespace std;

DPLexer::DPLexer(DPPlan *plan)
    : _content(0), _plan(plan), _token(_plan), _start(0), _limit(0)
{
    _parser = dPParseAlloc(malloc);
}

DPLexer::~DPLexer()
{
    dPParseFree(_parser, free);
}

char *DPLexer::getTokenValue()
{
    return strndup(_start, _cursor - _start);
}

void DPLexer::debug(int a, char b)
{
    cout << "DEBUG " << a << " ; " << b << endl;
    cout << "_start = " << _start << endl;
}

int DPLexer::scan()
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
        [A-Za-z]            { return CALC_TOKEN_IDENT; }
        "+"                 { return CALC_TOKEN_PLUS; }
        "-"                 { return CALC_TOKEN_MINUS; }
        "("                 { return CALC_TOKEN_LPAR; }
        "["                 { return CALC_TOKEN_LBRA; }
        ")"                 { return CALC_TOKEN_RPAR; }
        "]"                 { return CALC_TOKEN_RBRA; }
        ":"                 { return CALC_TOKEN_COLON; }
        "="                 { return CALC_TOKEN_EQUALS; }
        "?"                 { return CALC_TOKEN_INTERRO; }
        "//"                { return CALC_TOKEN_PARALLEL; }
        "!="                { return CALC_TOKEN_DISTINCT; }
        " "                 { _start++; goto cont; }
    */
}

void DPLexer::parse(const char *s)
{
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

}

bool DPLexer::getResult() const
{
    return _token.getResult();
}

