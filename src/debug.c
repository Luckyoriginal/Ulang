#include "debug.h"
#include <stdio.h>

// Helper to print operation types
static void print_op(OperationType op) {
    switch (op) {
        case OP_NONE:  printf("NONE"); break;
        case OP_NEG:   printf("- (NEG)"); break;
        case OP_ADD:   printf("+"); break;
        case OP_MINUS: printf("-"); break;
        case OP_MUL:   printf("*"); break;
        case OP_DIV:   printf("/"); break;
        default:       printf("?"); break;
    }
}

// Helper to handle visual indentation
static void print_indent(int indent_level) {
    for (int i = 0; i < indent_level; i++) {
        printf("  "); 
    }
}

// Helper for tokens (assuming a standard structure)
static void print_token(Token t) {
    // Replace with your actual token printing logic, e.g.:
    // printf("%.*s", t.length, t.start);
    printf("<token>%s", t.lexeme); 
}

void print_ast_node(const Compiler* c, unsigned int node_idx, int indent) {
    if (node_idx >= c->count) {
        print_indent(indent);
        printf("<Error: Invalid node index %u>\n", node_idx);
        return;
    }

    AST_Node* node = &c->AST_Tree[node_idx];
    print_indent(indent);

    switch (node->type) {
        case AST_Unary: 
            printf("UnaryOp [");
            print_op(node->as.unary.type);
            printf("]\n");
            print_ast_node(c, node->as.unary.right, indent + 1);
            break;

        case AST_Binary:
            printf("BinaryOp [");
            print_op(node->as.binary.type);
            printf("]\n");
            print_ast_node(c, node->as.binary.left, indent + 1);
            print_ast_node(c, node->as.binary.right, indent + 1);
            break;

        case AST_Variable:
            printf("Variable: ");
            print_token(node->as.variable.token);
	    if (node->as.variable.field != -1){
		    printf("\nwith field:\n ");
		    print_ast_node(c, node->as.variable.field, indent + 1);
	    }
            printf("\n");
            break;

        case AST_Constant: 
            printf("Constant: ");
            print_token(node->as.Constant.token);
            printf("\n");
            break;

        case AST_StructDef:
            printf("StructDef (Name: ");
            print_token(node->as.struct_def.Name);
            printf(", Fields: %u)\n", node->as.struct_def.field_count);
            for (unsigned int i = 0; i < node->as.struct_def.field_count; i++) {
                print_ast_node(c, node->as.struct_def.fields[i], indent + 1);
            }
            break;

        case AST_FieldDef:
            printf("FieldDef (Name: ");
            print_token(node->as.fields_def.Name);
            printf(", Type: ");
            print_token(node->as.fields_def.Type);
            printf(")\n");
            break;

        default:
            printf("Unknown Node Type (%d)\n", node->type);
            break;
    }
}

void print_ast(Compiler c, unsigned int root_index) {
    printf("=== AST Dump ===\n");
    if (c.count == 0) {
        printf("Tree is empty.\n");
        return;
    }
    print_ast_node(&c, root_index, 0);
    printf("================\n");
}
