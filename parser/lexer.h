#ifndef __LEXER_H__
#define __LEXER_H__
#include "plane.h"
#include "grammar-prot.h"

namespace DP {
class Lexer {
    const char *_content;
    Plane *_plane;
    ParserToken _token;
    void *_parser;
    const char *_start;
    const char *_marker;
    const char *_cursor;
    const char *_limit;
    int scan();

public:
    Lexer(Plane *plane);
    ~Lexer();
    char *getTokenValue();
    void debug(int a, char b);
    void parse(const char *s);
    bool getResult() const;
    std::string getLastContradiction() const;
};

}
#endif /* __LEXER_H__ */
