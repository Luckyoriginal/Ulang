#ifndef PARSE_EXPRESSION
#define PARSE_EXPRESSION
#include "lexer.h"
#include "parser.h"

typedef enum {
	PREC_NONE,
	PREC_ASSIGNEMENT,
	PREC_TERM,
	PREC_FACTOR,
	PREC_UNARY,
	PREC_PRIMARY,

}Precedence;

Precedence GetTokenPrecendence(TokenType type);

AST_Expression* ParsePrefix(Parser* parser);
AST_Expression* ParseInfix(Parser* parser,AST_Expression* left);

AST_Expression* ParseExpressionPrec(Parser* parser, Precedence precedence);
AST_Expression* ParseExpression(Parser* parser);
void DebugPrintAST(AST_Expression* expr);
#endif
