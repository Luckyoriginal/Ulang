#include "lexer_util.h"
#include "lexer.h"
#include <ctype.h>

void LexerUtilSkipWhiteSpace(Lexer *lexer){
	while (lexer->current_char != '\0' && isspace(lexer->current_char)) {
       		LexerAdvance(lexer);
    	}
}

bool LexerUtilSingleCharacter(Lexer *lexer, Token* token){
	switch (lexer->current_char) {
		case('('): 
			token->type = TOKEN_LBRACKET;
			token->lexem[0] = lexer->current_char;
			return true;
		case(')'): 
			token->type = TOKEN_RBRACKET;
			token->lexem[0] = lexer->current_char;
			return true;
		default:
			return false;
	}
}
