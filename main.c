#include <stdio.h>
#include "ast.h"

int main(){
	printf("hello world\n");
	Node root;
	Node a,b;
	create_constant_node(&a , 1.0);
	create_constant_node(&b , 1.0);
	create_binary_node( &root, ADDITION,&a,&b);
	print_ast(root,0);
	return 0;
}
