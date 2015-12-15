#include <iostream>
#include <cstring>
#include <malloc.h>
#include "dplexer.h"
#include "grammar.h"

using namespace std;

DPLexer::DPLexer()
    : m_content(0), m_plan(), m_token(m_plan), m_start(0), m_limit(0)
{
    m_parser = dPParseAlloc(malloc);
}

DPLexer::~DPLexer()
{
    dPParseFree(m_parser, free);
}

string DPLexer::getTokenValue() const
{
    return string(m_start, m_cursor - m_start);
}

void DPLexer::debug(int a, char b)
{
    cout << "DEBUG " << a << " ; " << b << endl;
    cout << "m_start = " << m_start << endl;
}

int DPLexer::scan()
{
    m_start = m_cursor;
#define YYCTYPE char
#define YYCURSOR m_cursor
#define YYLIMIT m_limit
#define YYMARKER m_marker
#define YYCTXMARKER m_ctxmarker
#define YYFILL(n)
#define YYDEBUG(a,b) debug(a, b)

cont:
    /*!re2c
        re2c:yyfill:enable = 0;

        "\000"              { return CALC_TOKEN_END; }
        "Let"               { return CALC_TOKEN_LET; }
        "Point"             { return CALC_TOKEN_POINT; }
        "Line"              { return CALC_TOKEN_LINE; }
        [A-Za-z]            { return CALC_TOKEN_IDENT; }
        "+"                 { return CALC_TOKEN_PLUS; }
        "-"                 { return CALC_TOKEN_MINUS; }
        "("                 { return CALC_TOKEN_LPAR; }
        ")"                 { return CALC_TOKEN_RPAR; }
        ":"                 { return CALC_TOKEN_COLON; }
        "="                 { return CALC_TOKEN_EQUALS; }
        " "                 { m_start++; goto cont; }
    */
}

void DPLexer::parse(const char *s)
{
    string word;
    int op_token;
    m_content = s;
    m_start = m_cursor = m_content;
    m_limit = m_content + strlen(m_content);

    do {
        op_token = scan();
        word = getTokenValue();
        dPParse(m_parser, op_token, const_cast<char *>(word.c_str()), &m_token);
    }
    while (op_token != CALC_TOKEN_END);

    dPParse(m_parser, 0, NULL, &m_token);

    cout << "finished!" << endl;
}
