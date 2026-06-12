#ifndef PARSER_H
#define PARSER_H
#define MAX_COUNT 255
#include "lexer.h"
#include <stdbool.h>

typedef struct {
	Lexer* lexer;
	Token current_token;
}Parser;

void ParserInit(Parser* parser, Lexer* lexer);
void ParserAdvance(Parser* parser);
bool ParserExpectedToken(Parser *parser, TokenType expected_type, const char* error_msg);

bool ParserCheck(Parser* parser, TokenType token);				//check but don't consume
bool ParserCheckConsume(Parser* parser, TokenType token);				//check and consume if the token type
void ParserMatch(Parser* parser, TokenType token, const char* error);	//check and must match
void ParserConsume(Parser* parser, TokenType token, const char* error);	//check, must match and consume
#endif
