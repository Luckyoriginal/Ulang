#include "parser.h"
#include "lexer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynarray.h"

void ParserInit(Parser *parser, Lexer *lexer){
	parser->lexer = lexer;
	parser->current_token = LexerNextToken(lexer);
}

void ParserAdvance(Parser *parser){
	parser->current_token = LexerNextToken(parser->lexer);
}

void ParserReportError(Parser* parser, const char* error_msg) {
	fprintf(stderr, "Syntax Error, %s. Got '%s'\n", error_msg, parser->current_token.lexeme);
	exit(1);
}

void ParserMatch(Parser *parser, TokenType expected_type, const char* error_msg) {
	if (parser->current_token.type != expected_type) {
		ParserReportError(parser, error_msg);
	}
}

bool ParserCheck(Parser *parser, TokenType expected_type) {
	if (parser->current_token.type == expected_type) {
		return true;
	}else{
		return false;
	}
}

bool ParserCheckConsume(Parser *parser, TokenType expected_type) {
	if (parser->current_token.type == expected_type) {
		ParserAdvance(parser);
		return true;
	}else{
		return false;
	}
}

void ParserConsume(Parser* parser, TokenType expected_type, const char* error_msg){	//check, must match and consume
	if (parser->current_token.type != expected_type) {
		ParserReportError(parser, error_msg);
	}else{
		ParserAdvance(parser);
	}
}

