#include "compiler.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

void CompilerInit(Compiler *c) {
	c->AST_Tree = malloc(sizeof(AST_Node));
	if (c->AST_Tree == NULL) {
		fprintf(stderr, "Out of memory during initialization\n");
		exit(1);
	}
	c->count = 0;
	c->capacity = 1;
}

unsigned int NewNode(Compiler *c) {
	if (c->count >= c->capacity) {
		unsigned int new_capacity = c->capacity * 2;

		AST_Node *temp = realloc(c->AST_Tree, new_capacity * sizeof(AST_Node));
		if (temp == NULL) {
			fprintf(stderr, "Out of memory during Node Allocation\n");
			CompilerFree(c);
			exit(1);
		}

		c->AST_Tree = temp;
		c->capacity = new_capacity;
	}

	unsigned int node_index = c->count;
	c->count++;

	return node_index;
}

void CompilerFree(Compiler *c) {
	if (c->AST_Tree != NULL) {
		free(c->AST_Tree);

		c->AST_Tree = NULL;
		c->count = 0;
		c->capacity = 0;
	}
}
