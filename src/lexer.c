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
	memset(token.lexem,0,sizeof(token.lexem)); //make it null
	
	LexerUtilSkipWhiteSpace(l);

	//if it is a single character token
	if (LexerUtilSingleCharacter(l, &token)){return token;}
}
