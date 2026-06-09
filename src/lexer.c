#include "lexer.h"
#include "lexer_util.h"
#include <string.h>

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

	//must be in this order:
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
	return token;
}
