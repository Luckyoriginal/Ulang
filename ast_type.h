#ifndef AST_TYPE
#define AST_TYPE
typedef enum NodeType {
	CONSTANT,
	BINARY,
	TERNARY,
}NodeType;

typedef enum ConstantType {
	FLOAT, INT, STRING, CHAR
}ConstantType;

typedef struct Constant {
	ConstantType type;
	union {
		float Float;
		int Int;
		char* String;
		char Char;
	};
}Constant;

typedef struct Node Node;

typedef enum BinaryType{
	ADDITION,
}BinaryType;

typedef struct Binary{
	BinaryType type;
	Node *a;
	Node *b;
}Binary;

typedef enum TernaryType{
	IFELSE,
}TernaryType;

typedef struct Ternary{
	TernaryType type;
	Node *a;
	Node *b;
	Node *c;
}Ternary;

struct Node{
	NodeType type;
	union {
		Constant constant;
		Binary binary;
		Ternary ternary;
	};
};

#endif
