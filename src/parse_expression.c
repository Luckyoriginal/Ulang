#include "parse_expression.h"
#include "ast.h"
#include "compiler.h"
#include "lexer.h"
#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// --- 1. Function Pointers & Rule Table ---

typedef unsigned int (*ParsePrefixFn)(Parser* parser, Compiler *c);
typedef unsigned int (*ParseInfixFn)(Parser* parser, Compiler* c, unsigned int left);

typedef struct {
	ParsePrefixFn prefix;
	ParseInfixFn infix;
	Precedence precedence;
} ParseRule;

// Forward declarations for the table
unsigned int ParseNumber(Parser* parser, Compiler* c);
unsigned int ParseVariable(Parser* parser, Compiler* c);
unsigned int ParseGrouping(Parser* parser, Compiler* c);
unsigned int ParseUnary(Parser* parser, Compiler* c);
unsigned int ParseInfix(Parser* parser,Compiler*c, unsigned int left);

ParseRule rules[] = {
	[TOKEN_LPARENTHESIS] = {ParseGrouping, NULL,PREC_NONE},
	[TOKEN_RPARENTHESIS] = {NULL, NULL,PREC_NONE},

	[TOKEN_IDENTIFIER] = {ParseVariable, NULL,       PREC_NONE},
	[TOKEN_NUMBER] = {ParseNumber, NULL,       PREC_NONE},
	[TOKEN_MINUS]  = {ParseUnary,  ParseInfix, PREC_TERM},
	[TOKEN_PLUS]   = {NULL,        ParseInfix, PREC_TERM},
	[TOKEN_STAR]   = {NULL,        ParseInfix, PREC_FACTOR},
	[TOKEN_DIVIDE] = {NULL,        ParseInfix, PREC_FACTOR},
};

ParseRule* GetRule(TokenType type) {
	return &rules[type];
}

// --- 2. Node Constructors ---

unsigned int MakeBinaryNode(Compiler*c, OperationType op, unsigned int left, unsigned int right){
	unsigned int id = NewNode(c);
	AST_Node* node = &c->AST_Tree[id];
	node->type = AST_Binary;
	node->as.binary.type = op;
	node->as.binary.left = left;
	node->as.binary.right = right;
	return id;
}

OperationType TokenToBinaryOp(Token tok){
	switch (tok.type) {
		case TOKEN_PLUS:  return OP_ADD;
		case TOKEN_MINUS: return OP_MINUS;
		case TOKEN_STAR:  return OP_MUL;
		default:
		fprintf(stderr, " Expected operation, got '%s'\n", tok.lexeme);
		return OP_NONE;
	}
}

// --- 3. Prefix & Infix Parsers ---

unsigned int ParseNumber(Parser* parser, Compiler* c) {
	unsigned int id = NewNode(c);
	AST_Node* node = &c->AST_Tree[id];
	node->type = AST_Constant;
	node->as.Constant.token = parser->current_token;
	ParserAdvance(parser);
	return id;
}

unsigned int ParseVariable(Parser* parser, Compiler* c) {
	unsigned int id = NewNode(c);
	AST_Node* node = &c->AST_Tree[id];
	node->type = AST_Variable;
	node->as.variable.token = parser->current_token;
	ParserAdvance(parser);
	if (ParserCheck(parser, TOKEN_DOT)){
		ParserAdvance(parser);
		ParserMatch(parser , TOKEN_IDENTIFIER, "expected identifier");
		node->as.variable.field = ParseVariable(parser , c);
	}else{
		node->as.variable.field = -1;
	}
	return id;
}

unsigned int ParseUnary(Parser* parser, Compiler *c) {
	ParserAdvance(parser); // consume operator 
	unsigned int right = ParseExpressionPrec(parser,c, PREC_UNARY);
	unsigned int id = NewNode(c);
	AST_Node* node = &c->AST_Tree[id];
	node->type = AST_Unary;
	node->as.unary.type = OP_NEG; //for now just neg
	node->as.unary.right = right;
	return id;
}

unsigned int ParseInfix(Parser* parser, Compiler* c, unsigned int left){
	Token op_token = parser->current_token;
	Precedence op_prec = GetRule(op_token.type)->precedence;
	ParserAdvance(parser);

	unsigned int right = ParseExpressionPrec(parser, c, op_prec);
	return MakeBinaryNode(c,TokenToBinaryOp(op_token), left, right);
}

unsigned int ParseGrouping(Parser* parser, Compiler*c){
	ParserAdvance(parser);
	
	unsigned int id = ParseExpressionPrec(parser,c, PREC_NONE);

	ParserConsume(parser, TOKEN_RPARENTHESIS, "expected ')' after expression ");
	return id;
}

// --- 4. The Core Parsing Engine ---

unsigned int ParseExpressionPrec(Parser* parser, Compiler* c, Precedence precedence){
	// 1. Look up the prefix rule for the current token
	ParsePrefixFn prefixRule = GetRule(parser->current_token.type)->prefix;

	if (prefixRule == NULL) {
		fprintf(stderr, "Syntax Error, Expected expression, got '%s'\n", parser->current_token.lexeme);
		exit(1);
		return 0;
	}

	// 2. Execute it to get the left-hand side
	unsigned int left = prefixRule(parser,c);

	// 3. Keep parsing as long as the next token has a higher precedence
	while (precedence < GetRule(parser->current_token.type)->precedence) {
		ParseInfixFn infixRule = GetRule(parser->current_token.type)->infix;
		left = infixRule(parser,c, left);
	}

	return left;
}

unsigned int ParseExpression(Parser* parser,Compiler*c ){
	return ParseExpressionPrec(parser,c, PREC_NONE);
}

