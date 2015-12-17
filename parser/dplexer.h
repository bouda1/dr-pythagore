#ifndef __DPLEXER_H__
#define __DPLEXER_H__
#include "dpplan.h"
#include "grammar-prot.h"

class DPLexer {
    const char *_content;
    DPPlan _plan;
    DPParserToken _token;
    void *_parser;
    const char *_start;
    const char *_marker;
    const char *_cursor;
    const char *_limit;
    int scan();

public:
    DPLexer();
    ~DPLexer();
    char *getTokenValue();
    void debug(int a, char b);
    void parse(const char *s);
};

#endif /* __DPLEXER_H__ */
