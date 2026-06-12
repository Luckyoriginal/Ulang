#ifndef COMPILER
#define COMPILER
#include "ast.h"

typedef struct {
	AST_Node* AST_Tree;
	unsigned int count;
	unsigned int capacity;
}Compiler;

void CompilerInit(Compiler *c);
unsigned int NewNode(Compiler *c);
void CompilerFree(Compiler *c);
#endif
