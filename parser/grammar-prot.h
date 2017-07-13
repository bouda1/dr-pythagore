#ifndef __GRAMMAR_PROT_H__
#define __GRAMMAR_PROT_H__
#include "parsertoken.h"

#define dPParseTOKENTYPE char *
#define dPParseARG_PDECL , DP::ParserToken *token

void dPParse(void *yyp, int yymajor, dPParseTOKENTYPE yyminor dPParseARG_PDECL);
void dPParseFree(void *p, void(*freeProc)(void *));
void *dPParseAlloc(void *(*mallocProc)(size_t));

#if !defined(NDEBUG)
void dPParseTrace(FILE *TraceFILE, char *zTracePrompt);
#endif

#endif /* __GRAMMAR_PROT_H__ */
