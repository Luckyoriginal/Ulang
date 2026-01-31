#include "ast.h"
#include "ast_type.h"
#include <stdio.h>
#include <string.h>

void create_constant_node(Node* node, float value){
	node->type = CONSTANT;
	node->constant.type = FLOAT;
	node->constant.Float = value;
}

void create_binary_node(Node *node, BinaryType type, Node *a, Node*b){
	node->type = BINARY;
	node->binary.type = type;
	node->binary.a = a;
	node->binary.b = b;
}

void create_ternary_node(Node *node, TernaryType type, Node *a, Node*b, Node* c){
	node->type = TERNARY;
	node->ternary.type = type;
	node->ternary.a = a;
	node->ternary.b = b;
	node->ternary.c = c;
}

void create_variable_node(Node *node, ConstantType type, const char name[MAX_NAME_LENGTH]) {
	node->type = VARIABLE;
	strcpy(node->variable.name, name);
}

void print_ast(Node root, int level){
	for (int i=0;i<level;i++){printf(" ");}
	switch (root.type) {
		case CONSTANT:
			printf("CONSTANT: %f\n", root.constant.Float);
			break;

		case BINARY:
			printf("Binary operation ");
			if (root.binary.a != NULL && root.binary.b != NULL) {
				print_binary(root, level);
			}
			break;

		case TERNARY:
			printf("Ternary operation ");
			if (root.ternary.a != NULL && root.ternary.b != NULL && root.ternary.c != NULL) {
				print_ternary(root, level);
			}
			break;

		case VARIABLE:
			print_variable(root, level);
			break;

		default:
			// Optional: handle unknown node types
			fprintf(stderr, "Unknown AST node type!\n");
			break;
	}

}


void print_binary(Node root, int level){
	for (int i=0;i<level;i++){printf(" ");}
	if (root.binary.type == ADDITION){
		printf("addition:\n");
		print_ast(*root.binary.a, level+SPACING);
		print_ast(*root.binary.b, level+SPACING);
	}
}

void print_ternary(Node root, int level){
	for (int i=0;i<level;i++){printf(" ");}
	if (root.ternary.type == IFELSE){
		printf("if:\n");
		print_ast(*root.ternary.a, level+SPACING);
		for (int i=0;i<level;i++){printf(" ");}
		printf("then:\n");
		print_ast(*root.ternary.b, level+SPACING);
		for (int i=0;i<level;i++){printf(" ");}
		printf("else:\n");
		print_ast(*root.ternary.c, level+SPACING);
	}
}

void print_variable(Node root, int level){
	for (int i=0;i<level;i++){printf(" ");}
	printf("variable: %s\n",root.variable.name);
}
