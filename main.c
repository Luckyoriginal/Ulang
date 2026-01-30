#include <stdio.h>

typedef enum NodeType {
	CONSTANT,
	BINARY,
	TERNARY,
}NodeType;

typedef enum ConstantType {
	FLOAT, INT, STRING, CHAR
}ConstantType;

typedef struct Constant {
	ConstantType type;
	union {
		float Float;
		int Int;
		char* String;
		char Char;
	};
}Constant;

typedef struct Node Node;

typedef enum BinaryType{
	ADDITION,
}BinaryType;

typedef struct Binary{
	BinaryType type;
	Node *a;
	Node *b;
}Binary;

typedef enum TernaryType{
	IFELSE,
}TernaryType;

typedef struct Ternary{
	TernaryType type;
	Node *a;
	Node *b;
	Node *c;
}Ternary;

struct Node{
	NodeType type;
	union {
		Constant constant;
		Binary binary;
		Ternary ternary;
	};
};


void create_node_constant(Node* node, float value){
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

#define SPACING 3
void print_ast(Node root, int level){
	for (int i=0;i<level;i++){
		printf(" ");
	}
	if (root.type==CONSTANT){
		printf("CONSTANT: %f\n",root.constant.Float);
	}
	if (root.type==BINARY){
		printf("Binary operation");
		if (root.binary.a!=NULL && root.binary.b!=NULL){
			if (root.binary.type == ADDITION){
				printf(" addition:\n");
				print_ast(*root.binary.a, level+SPACING);
				print_ast(*root.binary.b, level+SPACING);
			}
		}
	}
	if (root.type==TERNARY){
		printf("Ternary operation");
		if (root.ternary.a!=NULL && root.ternary.b!=NULL && root.ternary.c!=NULL){
			if (root.ternary.type == IFELSE){
				printf("if:\n");
				print_ast(*root.ternary.a, level+SPACING);
				printf("then:\n");
				print_ast(*root.ternary.b, level+SPACING);
				printf("else:\n");
				print_ast(*root.ternary.c, level+SPACING);
			}
		}
	}
}

int main(){
	printf("hello world\n");
	Node root;
	Node a,b;
	create_node_constant(&a , 1.0);
	create_node_constant(&b , 1.0);
	create_binary_node( &root, ADDITION,&a,&b);
	print_ast(root,0);
	return 0;
}
