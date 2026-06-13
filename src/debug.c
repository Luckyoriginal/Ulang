#include <stdbool.h>
#include <stdio.h>
#include <limits.h> // Added for UINT_MAX
#include "debug.h"
#include "ast.h"

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

// Upgraded helper for visual tree branches
static void print_indent(int indent_level) {
    for (int i = 0; i < indent_level; i++) {
        if (i == indent_level - 1) {
            printf(" |-- ");
        } else {
            printf(" |   ");
        }
    }
}

static void print_token(Token t) {
    printf("%s", t.lexeme); 
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
            printf("Variable [");
            print_token(node->as.variable.token);
            printf("]\n"); 

            if (node->as.variable.field != UINT_MAX) {
                print_indent(indent + 1);
                printf("-> Field Access:\n");
                print_ast_node(c, node->as.variable.field, indent + 2);
            }

            if (node->as.variable.is_function) {
                print_indent(indent + 1);
                printf("-> Function Call (Args: %u)\n", node->as.variable.parameter_count);
                for (unsigned int i = 0; i < node->as.variable.parameter_count; i++) {
                    print_ast_node(c, node->as.variable.parameters[i], indent + 2);
                }
            }
            break;

        case AST_Constant: 
            printf("Constant [");
            print_token(node->as.constant.token);
            printf("]\n");
            break;
            
        case AST_StatementEqual:
            printf("StatementEqual [=]\n");
            print_ast_node(c, node->as.statement_equal.left, indent + 1);
            print_ast_node(c, node->as.statement_equal.right, indent + 1);
            break;

        case AST_StructDef:
            printf("StructDef [");
            print_token(node->as.struct_def.Name);
            printf("] (Fields: %u)\n", node->as.struct_def.field_count);
            for (unsigned int i = 0; i < node->as.struct_def.field_count; i++) {
                print_ast_node(c, node->as.struct_def.fields[i], indent + 1);
            }
            break;

        case AST_FieldDef:
            printf("FieldDef [");
            print_token(node->as.fields_def.Name);
            printf("] Type: ");
            print_token(node->as.fields_def.Type);
            printf("\n");
            break;

        // --- NEW BLOCK HANDLING ---
        case AST_Block:
            printf("BlockNode\n");
            
            // Print the current statement in the block
            print_indent(indent + 1);
            printf("-> Statement:\n");
            print_ast_node(c, node->as.block.statement, indent + 2);

            // Print the rest of the block sequence, avoiding 'Invalid Index' errors
            if (node->as.block.next != UINT_MAX) {
                print_indent(indent + 1);
                printf("-> Next:\n");
                print_ast_node(c, node->as.block.next, indent + 2);
            }
            break;

        default:
            printf("<Unknown Node Type: %d>\n", node->type);
            break;
    }
}

// Pass Compiler by constant pointer to prevent massive memory copying!
void print_ast(const Compiler* c, unsigned int root_index) {
    printf("\n=== AST Dump ===\n");
    if (c->count == 0) {
        printf("Tree is empty.\n");
        return;
    }
    print_ast_node(c, root_index, 0);
    printf("================\n\n");
}
