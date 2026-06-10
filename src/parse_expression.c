#include "parse_expression.h"
#include "lexer.h"
#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Precedence GetTokenPrecendence(TokenType type){
	switch (type){
		case TOKEN_PLUS:
		case TOKEN_MINUS: return PREC_TERM;
		case TOKEN_STAR: 
		case TOKEN_DIVIDE: return PREC_FACTOR;
		default: return PREC_NONE;
	}
}


AST_Expression* ParseExpressionPrec(Parser* parser, Precedence precedence){
	AST_Expression* left = ParsePrefix(parser);
	if (left==NULL){
		return NULL;
	}

	while (precedence<GetTokenPrecendence(parser->current_token.type)){
		left = ParseInfix(parser , left);
	}

	return left;
}

AST_Expression* ParseExpression(Parser* parser){
	return ParseExpressionPrec(parser, PREC_NONE);
}

AST_Expression* ParsePrefix(Parser* parser) {
	AST_Expression* expr = malloc(sizeof(AST_Expression));
	//handle constant
	if (parser->current_token.type == TOKEN_NUMBER){
		expr->type = PRIMARY;
		strcpy(expr->as.constant.value,parser->current_token.lexeme);
		ParserAdvance(parser);
		return expr;
	}

	//handle unary
	if (parser->current_token.type == TOKEN_MINUS) {
		ParserAdvance(parser);
		AST_Expression* right = ParseExpressionPrec(parser,PREC_UNARY);
		expr->type = UNARY;
		expr->as.unary.type=OP_NEG;
		return expr;
	}

	fprintf(stderr, "Syntax Error, Expected expression, got '%s'\n",parser->current_token.lexeme);
	return NULL;
}

OperationType TokenToBinaryOp(Token tok){
	switch (tok.type) {
		case TOKEN_PLUS:
			return OP_ADD;
		case TOKEN_MINUS:
			return OP_MINUS;
		case TOKEN_STAR:
			return OP_MUL;
		default:
			fprintf(stderr, " Expected operation, got '%s'\n",tok.lexeme);
			return OP_NONE;
	}
}

AST_Expression* ParseInfix(Parser* parser, AST_Expression* left){
	TokenType op_type = parser->current_token.type;
	Precedence op_prec = GetTokenPrecendence(op_type);

	AST_Expression* right = ParseExpressionPrec(parser , op_prec);
	AST_Expression* expr = malloc(sizeof(AST_Expression));
	expr->type = BINARY;
	expr->as.binary.type = TokenToBinaryOp(parser->current_token);
	expr->as.binary.left_node = left;
	expr->as.binary.right_node = right;

	return expr;
}
