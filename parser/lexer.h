#ifndef __LEXER_H__
#define __LEXER_H__
#include "plan.h"
#include "grammar-prot.h"

class DPLexer {
    const char *_content;
    DPPlan *_plan;
    DPParserToken _token;
    void *_parser;
    const char *_start;
    const char *_marker;
    const char *_cursor;
    const char *_limit;
    int scan();

public:
    DPLexer(DPPlan *plan);
    ~DPLexer();
    char *getTokenValue();
    void debug(int a, char b);
    void parse(const char *s);
    bool getResult() const;
};

#endif /* __LEXER_H__ */
