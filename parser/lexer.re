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
#include <iostream>
#include <cstring>
#include <malloc.h>
#include "lexer.h"
#include "grammar.h"

using namespace std;
using namespace DP;

/**
 * @brief Lexer::Lexer Constructor
 * @param plan The plane associated to the lexer.
 */
Lexer::Lexer(Plane *plane)
    : _content(0)
    , _plane(plane)
    , _token(_plane)
    , _start(0)
    , _limit(0)
{
    _parser = dPParseAlloc(malloc);
}

/**
 * @brief Lexer::~Lexer Destructor
 */
Lexer::~Lexer()
{
    dPParseFree(_parser, free);
}

/**
 * @brief Lexer::getTokenValue returns a token value, the current value to be
 * parsed.
 * @return A string as char *
 */
char *Lexer::getTokenValue()
{
    return strndup(_start, _cursor - _start);
}

void Lexer::debug(int a, char b)
{
    cout << "DEBUG " << a << " ; " << b << endl;
    cout << "_start = " << _start << endl;
}

/**
 * @brief Lexer::scan The main function, it finds tokens.
 * @return 0 on success
 */
int Lexer::scan()
{
    _start = _cursor;
#define YYCTYPE char
#define YYCURSOR _cursor
#define YYLIMIT _limit
#define YYMARKER _marker
#define YYCTXMARKER _ctxmarker
#define YYFILL(n)
#define YYDEBUG(a, b) debug(a, b)

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
        "And"               { return CALC_TOKEN_AND; }
        "Or"               { return CALC_TOKEN_OR; }
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

/**
 * @brief Lexer::parse The main loop that calls the scan() function.
 * @param s The full string to parse
 */
void Lexer::parse(const char *s)
{
    FILE *f = fopen("/tmp/parser.dbr", "a");
    dPParseTrace(f, "DP => ");
    char *word;
    int op_token;
    _content = s;
    _start = _cursor = _content;
    _limit = _content + strlen(_content);
    _token.setError(false);
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

/**
 * @brief Lexer::getResult Gives an answer to a question. It can be true or
 * false.
 * @return a boolean
 */
bool Lexer::getResult() const
{
    return _token.getResult();
}

/**
 * @brief Lexer::getLastContradiction Returns the last error
 * @return A string
 */
string Lexer::getLastContradiction() const
{
    return _plane->getLastContradiction();
}
