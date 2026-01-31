#ifndef AST
#define AST
#include "ast_type.h"

//node creations utility
void create_constant_node(Node* node, float value);
void create_binary_node(Node *node, BinaryType type, Node *a, Node*b);
void create_ternary_node(Node *node, TernaryType type, Node *a, Node*b, Node* c);
void create_variable_node(Node *node, ConstantType type, const char name[MAX_NAME_LENGTH]);

//debugging function
#define SPACING 3

void print_ast(Node root, int level);
void print_constant(Node root, int level);
void print_binary(Node root, int level);
void print_ternary(Node root, int level);
void print_variable(Node root, int level);
#endif
