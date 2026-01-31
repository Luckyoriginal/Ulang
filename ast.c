#include "ast.h"
#include <stdio.h>

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

void create_ternary_node(Node *node, BinaryType type, Node *a, Node*b, Node* c){
	node->type = TERNARY;
	node->ternary.type = type;
	node->ternary.a = a;
	node->ternary.b = b;
	node->ternary.c = c;
}

void print_ast(Node root, int level){
	for (int i=0;i<level;i++){printf(" ");}
	if (root.type==CONSTANT){
		printf("CONSTANT: %f\n",root.constant.Float);
	}
	if (root.type==BINARY){
		printf("Binary operation");
		if (root.binary.a!=NULL && root.binary.b!=NULL){
			print_binary(root , level);
		}
	}
	if (root.type==TERNARY){
		printf("Ternary operation");
		if (root.ternary.a!=NULL && root.ternary.b!=NULL && root.ternary.c!=NULL){
			print_ternary(root , level);
		}
		
	}
}


void print_binary(Node root, int level){
	for (int i=0;i<level;i++){printf(" ");}
	if (root.binary.type == ADDITION){
		printf(" addition:\n");
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


