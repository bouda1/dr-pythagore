#ifndef __DPLEXER_H__
#define __DPLEXER_H__
#include "dpplan.h"
#include "grammar-prot.h"

class DPLexer {
    const char *m_content;
    DPPlan m_plan;
    DPParserToken m_token;
    void *m_parser;
    const char *m_start;
    const char *m_marker;
    const char *m_cursor;
    const char *m_limit;
    int scan();

public:
    DPLexer();
    ~DPLexer();
    char *getTokenValue();
    void debug(int a, char b);
    void parse(const char *s);
};

#endif /* __DPLEXER_H__ */
