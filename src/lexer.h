#ifndef LEXER_H
#define LEXER_H

//token structure 
typedef enum {
	TOKEN_EOF,
	TOKEN_IDENTIFIER,
	TOKEN_NUMBER,
	
	TOKEN_SEMICOLON,
	TOKEN_COMMA,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_STAR,
	TOKEN_EQUAL,
	TOKEN_DIVIDE,

	TOKEN_LBRACKET,
	TOKEN_RBRACKET,
	TOKEN_LBRACE,
	TOKEN_RBRACE,
	TOKEN_LPARENTHESIS,
	TOKEN_RPARENTHESIS,
	
	TOKEN_STRUCT,
	TOKEN_ENUM,
	TOKEN_FUNC,
	TOKEN_TYPE,
}TokenType;

typedef struct {
	TokenType type;
	char lexeme[64];
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
