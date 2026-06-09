#ifndef TYPE_H
#define TYPE_H
#include "parser.h"

typedef struct {
	AST_Struct_Definition structures[255];
	int structures_count;
}Types;

void ParseAllTypes(Parser* parser, Types* type);
#endif
