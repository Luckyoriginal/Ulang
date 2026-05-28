#ifndef LEXER_UTIL_H
#define LEXER_UTIL_H
#include "lexer.h"
#include <stdbool.h>

void LexerUtilSkipWhiteSpace(Lexer*l);

bool LexerUtilSingleCharacter(Lexer*l,Token* token);

//utility for multiple character:
bool LexerUtilMultiCharacter(Lexer*l,Token* token);

bool LexerUtilNumber(Lexer*l,Token* token);

bool LexerIsReserved(Token* token);
#endif
