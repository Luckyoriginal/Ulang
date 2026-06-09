#ifndef PARSER_H
#define PARSER_H
#define MAX_COUNT 255
#include "lexer.h"
#include <stdbool.h>

typedef struct {
	Lexer* lexer;
	Token current_token;
}Parser;

void ParserInit(Parser* parser, Lexer* lexer);
void ParserAdvance(Parser* parser);
bool ParserExpectedToken(Parser *parser, TokenType expected_type, const char* error_msg);


//parser types:

typedef struct {
	char type_name[64];
	char field_name[64];
}AST_Field_Declaration;

bool ParserParseField(Parser* parser, AST_Field_Declaration* field);

typedef struct {
	char struct_name[64];
	int field_count;
	AST_Field_Declaration fields[10];
}AST_Struct_Definition;

typedef struct {
	char enum_name[64];
	int field_count;
	char* fields[10];
}AST_Enum_Definition;


typedef struct {
	char function_name[64];
	int argument_count;
	char argument_name[10][64];
	char argument_type[10][64];
	char return_type[64];
}AST_Function_Definition;

//compiler parsing
typedef struct {
	AST_Struct_Definition structure[MAX_COUNT];
	int structure_count;
	AST_Function_Definition functions[MAX_COUNT];
	int function_count;
}Compiler;

void InitCompiler(Compiler* c);
void ParseFile(Compiler* c, Parser* p);

bool ParseTypeDefinition(Parser* parser, Compiler* c);
bool ParseFunctionDefinition(Parser* parser, Compiler* c);

#endif
