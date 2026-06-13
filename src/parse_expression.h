#ifndef PARSE_EXPRESSION
#define PARSE_EXPRESSION
#include <stdbool.h>
#include "lexer.h"
#include "ast.h"
#include "parser.h"
#include "compiler.h"

typedef enum {
	PREC_NONE,
	PREC_ASSIGNEMENT,
	PREC_TERM,
	PREC_FACTOR,
	PREC_UNARY,
	PREC_PRIMARY,

}Precedence;

Precedence GetTokenPrecendence(TokenType type);

unsigned int ParsePrefix(Parser* parser, Compiler* c);
unsigned int ParseInfix(Parser* parser, Compiler* c,unsigned int left);

unsigned int ParseExpressionPrec(Parser* parser, Compiler* c, Precedence precedence);
unsigned int ParseExpression(Parser* parser, Compiler* c);

unsigned int ParseNumber(Parser* parser, Compiler* c);
unsigned int ParseVariable(Parser* parser, Compiler* c);
unsigned int ParseGrouping(Parser* parser, Compiler* c);
unsigned int ParseUnary(Parser* parser, Compiler* c);
unsigned int ParseInfix(Parser* parser,Compiler*c, unsigned int left);


//void DebugPrintAST(AST_Expression* expr);
#endif
