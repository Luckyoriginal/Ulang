#include <stdio.h>

typedef enum NodeType {
	CONSTANT,
}NodeType;

typedef struct Node{
	NodeType type;
	union {
		float value;
	};
}Node;

void create_node_constant(Node* node, float value){
	node->type = CONSTANT;
	node->value = value;
}

void print_ast(Node root){
	if (root.type==CONSTANT){
		printf("CONSTANT: %f\n",root.value);
	}
}
int main(){
	printf("hello world\n");
	Node root;
	create_node_constant(&root,3);
	print_ast(root);
	return 0;
}
