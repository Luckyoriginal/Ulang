#ifndef LEXER_H
#define LEXER_H

//token structure 
typedef enum {
	TOKEN_IDENTIFIER,
	TOKEN_LBRACKET,
	TOKEN_RBRACKET,
}TokenType;

typedef struct {
	TokenType type;
	char lexem[64];
}Token;

//lexer structure:
typedef struct {
	const char* source;
	int position;
	char current_char;
}Lexer;

//lexer function:
void LexerInit(Lexer*,const char* source);
void LexerAdvance(Lexer*);

//token function:
Token LexerNextToken(Lexer* l);
#endif
