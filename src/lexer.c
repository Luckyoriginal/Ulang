#include "lexer.h"
#include "lexer_util.h"
#include <string.h>
#include <stdio.h>

void LexerInit(Lexer *l, const char *source){
	l->current_char = source[0];
	l->position = 0;
	l->source = source;
}

void LexerAdvance(Lexer *l){
	l->position++;
	l->current_char = l->source[l->position];
}

Token LexerNextToken(Lexer *l){
	Token token;
	memset(token.lexeme,0,sizeof(token.lexeme)); //make it null
	
	LexerUtilSkipWhiteSpace(l);

	//if it is a single character token
	if (LexerUtilSingleCharacter(l, &token)){return token;}

	if (LexerUtilNumber(l , &token)){
		token.type = TOKEN_NUMBER;
		return token;
	}

	if (LexerUtilMultiCharacter(l , &token)){
		if (LexerIsReserved(&token)){return token;}
		else { 
			token.type = TOKEN_IDENTIFIER;
			return token;
		}
	}

	printf("error, token not recognized\n");
	return token;
}
