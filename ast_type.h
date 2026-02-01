#ifndef AST_TYPE
#define AST_TYPE
#define MAX_NAME_LENGTH 128
//--------enum here----------//
typedef enum NodeType {
	CONSTANT,
	BINARY,
	TERNARY,
	VARIABLE,
}NodeType;

typedef enum ConstantType {
	FLOAT, INT, STRING, CHAR
}ConstantType;

typedef enum BinaryType{
	ADDITION, SEQUENCE
}BinaryType;

typedef enum TernaryType{
	IFELSE,
}TernaryType;

//--------struct here----------//

typedef struct Node Node;

typedef struct Constant {
	ConstantType type;
	union {
		float Float;
		int Int;
		char* String;
		char Char;
	};
}Constant;

typedef struct Binary{
	BinaryType type;
	Node *a;
	Node *b;
}Binary;

typedef struct Ternary{
	TernaryType type;
	Node *a;
	Node *b;
	Node *c;
}Ternary;

typedef struct Variable{
	ConstantType type;
	char name[MAX_NAME_LENGTH];
}Variable;

struct Node{
	NodeType type;
	union {
		Constant constant;
		Binary binary;
		Ternary ternary;
		Variable variable;
	};
};

#endif
