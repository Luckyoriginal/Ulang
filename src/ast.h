#ifndef AST_H
#define AST_H
#include "lexer.h"
#define MAX_FIELD 32

typedef enum {
	OP_NONE,
	//unary
	OP_NEG,

	//binary
	OP_ADD,
	OP_MINUS,
	OP_MUL,
	OP_DIV,
}OperationType;

typedef enum {
	AST_Unary,		
	AST_Binary,		
	AST_Variable,		
	AST_Constant,		
	AST_StructDef,		
	AST_FieldDef,		
	//statement
	AST_StatementEqual,
	AST_Block,
}AST_NodeType;


//we use unsigned int as node reference since we'll put node inside a long array, this would be fast for cache
typedef struct {
	AST_NodeType type;
	union{
		struct{
			OperationType type;	
			unsigned int right;
		}unary;

		struct {
			OperationType type;	
			unsigned int left;
			unsigned int right;
		}binary;

		struct {
			Token token;
			bool is_function;
			unsigned int field; //for structure variable
			unsigned int parameter_count;
			unsigned int parameters[MAX_FIELD];
		}variable;

		struct {
			Token token;
		}constant;
		
		struct {
			unsigned int left;
			unsigned int right;
		}statement_equal;

		struct {
			unsigned int statement;
			unsigned int next;
		}block;

		struct {
			Token Name;
			unsigned int field_count;
			unsigned int fields[MAX_FIELD];
		}struct_def;

		struct {
			Token Name;
			Token Type;
		}fields_def;
	}as;
}AST_Node;
#endif
