#include <stdio.h>
#include "ast.h"
#include "ast_type.h"

int main(){
	Node root;
	Node a,b,c;
	create_constant_node(&a , 1.0);
	create_constant_node(&b , 2.0);
	create_constant_node(&c , 3.0);
	Node x;
	create_variable_node(&x,INT,"x");
	create_ternary_node( &root, IFELSE,&a,&b, &x);
	print_ast(root,0);
	return 0;
}
