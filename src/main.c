#include <stdio.h>
#include "lexer.h"

int main(){
	Lexer lexer;
	LexerInit(&lexer," ( ) int x 12 1.2 .3");
	printf("token %s\n",LexerNextToken(&lexer).lexeme);
	printf("token %s\n",LexerNextToken(&lexer).lexeme);
	printf("token %s\n",LexerNextToken(&lexer).lexeme);
	printf("token %s\n",LexerNextToken(&lexer).lexeme);
	printf("token %s\n",LexerNextToken(&lexer).lexeme);
	printf("token %s\n",LexerNextToken(&lexer).lexeme);
	printf("token %s\n",LexerNextToken(&lexer).lexeme);
	return 0;
}
