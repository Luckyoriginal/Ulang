#include <stdio.h>
#include "ast.h"
#include "ast_type.h"
#include "parser.h"

int main(int argc, char *argv[]){
	char buffer[100000];
	char* cursor = buffer;
	while (--argc >0){
		open_file(argv[argc],buffer);
		parse_file(&cursor);
	}
	return 0;
}
