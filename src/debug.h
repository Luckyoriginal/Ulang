#ifndef DEBUG_H
#define DEBUG_H
#include "ast.h"
#include "compiler.h"

void print_ast(const Compiler *c, unsigned int root_index);
#endif
