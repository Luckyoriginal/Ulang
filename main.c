#include <stdio.h>

typedef enum NodeType {
	BLOCK,
}NodeType;

typedef struct Node{
	NodeType type;
}Node;

void create_node_block(Node* node){
	node->type = BLOCK;
}
int main(){
	printf("hello world\n");
	return 0;
}
