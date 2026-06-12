#include "lexer_util.h"
#include "lexer.h"
#include <ctype.h>
#include <string.h>

void LexerUtilSkipWhiteSpace(Lexer *lexer){
	while (lexer->current_char != '\0' && isspace(lexer->current_char)) {
       		LexerAdvance(lexer);
    	}
}

bool LexerUtilSingleCharacter(Lexer *lexer, Token* token){
	switch (lexer->current_char) {
		case('('): 
			token->type = TOKEN_LPARENTHESIS;
			token->lexeme[0] = lexer->current_char;
			LexerAdvance(lexer);
			return true;
		case(')'): 
			token->type = TOKEN_RPARENTHESIS;
			token->lexeme[0] = lexer->current_char;
			LexerAdvance(lexer);
			return true;
		case(';'): 
			token->type = TOKEN_SEMICOLON;
			token->lexeme[0] = lexer->current_char;
			LexerAdvance(lexer);
			return true;
		case(','): 
			token->type = TOKEN_COMMA;
			token->lexeme[0] = lexer->current_char;
			LexerAdvance(lexer);
			return true;
		case('.'): 
			token->type = TOKEN_DOT;
			token->lexeme[0] = lexer->current_char;
			LexerAdvance(lexer);
			return true;
		case('+'): 
			token->type = TOKEN_PLUS;
			token->lexeme[0] = lexer->current_char;
			LexerAdvance(lexer);
			return true;
		case('-'): 
			token->type = TOKEN_MINUS;
			token->lexeme[0] = lexer->current_char;
			LexerAdvance(lexer);
			return true;
		case('/'): 
			token->type = TOKEN_DIVIDE;
			token->lexeme[0] = lexer->current_char;
			LexerAdvance(lexer);
			return true;
		case('*'): 
			token->type = TOKEN_STAR;
			token->lexeme[0] = lexer->current_char;
			LexerAdvance(lexer);
			return true;
		case('='): 
			token->type = TOKEN_EQUAL;
			token->lexeme[0] = lexer->current_char;
			LexerAdvance(lexer);
			return true;
		case('{'): 
			token->type = TOKEN_LBRACE;
			token->lexeme[0] = lexer->current_char;
			LexerAdvance(lexer);
			return true;
		case('}'): 
			token->type = TOKEN_RBRACE;
			token->lexeme[0] = lexer->current_char;
			LexerAdvance(lexer);
			return true;
		case('\0'): 
			token->type = TOKEN_EOF;
			token->lexeme[0] = lexer->current_char;
			LexerAdvance(lexer);
			return true;

		default:
			return false;
	}
}

bool LexerUtilMultiCharacter(Lexer *l, Token *token){
	int i=0;
	while (isalnum(l->current_char) || l->current_char == '_') {
		token->lexeme[i++] = l->current_char;
		LexerAdvance(l);
	}
	if (i==0){
		return false;
	}else{
		return true;
	}
}

bool LexerUtilNumber(Lexer *l, Token *token){
	int i = 0;
	int has_dot = 0; 

	while (isdigit(l->current_char) || (l->current_char == '.' && !has_dot && i != 0)) {
		if (l->current_char == '.') {
			if (!isdigit(l->source[l->position + 1])) {
				break; 
			}
			has_dot = 1;  
		}

		token->lexeme[i++] = l->current_char;
		LexerAdvance(l);
	}

	if (i == 0) {
		return false;
	} else {
		return true;
	}
}

bool LexerIsReserved(Token *token){
	if (strcmp(token->lexeme, "struct")==0){
		token->type = TOKEN_STRUCT;
		return true;
	}
	if (strcmp(token->lexeme, "enum")==0){
		token->type = TOKEN_ENUM;
		return true;
	}
	if (strcmp(token->lexeme, "func")==0){
		token->type = TOKEN_FUNC;
		return true;
	}
	if (strcmp(token->lexeme, "type")==0){
		token->type = TOKEN_TYPE;
		return true;
	}

	return false;
}
