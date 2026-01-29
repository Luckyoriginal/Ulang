#include <stdio.h>

typedef enum NodeType {
	CONSTANT,
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

typedef struct Node{
	NodeType type;
	union {
		Constant constant;
	};
}Node;

void create_node_constant(Node* node, float value){
	node->type = CONSTANT;
	node->constant.type = FLOAT;
	node->constant.Float = value;
}

void print_ast(Node root){
	if (root.type==CONSTANT){
		printf("CONSTANT: %f\n",root.constant.Float);
	}
}

int main(){
	printf("hello world\n");
	Node root;
	create_node_constant(&root,3);
	print_ast(root);
	return 0;
}
