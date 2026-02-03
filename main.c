#include <stdio.h>
#include "ast.h"
#include "ast_type.h"
#include "parser.h"
#include "hashdict.h"

void compile(char* buffer){
	struct dictionary* functions = dic_new(0);

	dic_delete(functions);
}

int print_hash(void *key, int count, Identifier* value, void* user){
	printf("found %s of type %d",(char*)key, value->type);
}

int main(int argc, char *argv[]){
	char buffer[100000];
	char* cursor = buffer;
	struct dictionary* ids = dic_new(0);
	while (--argc >0){
		open_file(argv[argc],buffer);
		parse_file(&cursor, ids);
	}
	dic_forEach(ids, (enumFunc)print_hash, NULL);
	dic_delete(ids);
	return 0;
}
