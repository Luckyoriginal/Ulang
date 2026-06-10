#include "parser_util.h"
#include <stdio.h>

void PrintCompilerDebug(Compiler*c ){
	//printing all struct
	
	printf(" Structure:----------- \n");
	for (int i=0;i<c->structure_count;i++){
		printf("name %s\n",c->structure[i].struct_name);
		for (int j=0;j<c->structure[i].field_count;j++){
			printf("field name %s, of type %s\n",c->structure[i].fields[j].field_name,c->structure[i].fields[j].type_name);
		}
	}
	printf(" ----------- \n");

	printf(" function:----------- \n");
	for (int i=0;i<c->function_count;i++){
		printf("name %s\n",c->functions[i].function_name);
		for (int j=0;j<c->functions[i].argument_count;j++){
			printf("argument name %s, of type %s\n",c->functions[i].argument_name[j],c->functions[i].argument_type[j]);
		}
	}
	printf(" ----------- \n");
}
