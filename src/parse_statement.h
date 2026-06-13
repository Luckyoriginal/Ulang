#ifndef PARSE_STATEMENT_H
#define PARSE_STATEMENT_H
#include "compiler.h"
#include "parser.h"

unsigned int ParseStatement(Parser* parser, Compiler* c);
unsigned int ParseAssignement(Parser*p, Compiler* c);
unsigned int ParseBlock(Parser*p, Compiler* c);
#endif
