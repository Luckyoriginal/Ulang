#include "parse_expression.h"
#include "lexer.h"
#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// --- 1. Function Pointers & Rule Table ---

typedef AST_Expression* (*ParsePrefixFn)(Parser* parser);
typedef AST_Expression* (*ParseInfixFn)(Parser* parser, AST_Expression* left);

typedef struct {
    ParsePrefixFn prefix;
    ParseInfixFn infix;
    Precedence precedence;
} ParseRule;

// Forward declarations for the table
AST_Expression* ParseNumber(Parser* parser);
AST_Expression* ParseUnary(Parser* parser);
AST_Expression* ParseInfix(Parser* parser, AST_Expression* left);

ParseRule rules[] = {
    [TOKEN_NUMBER] = {ParseNumber, NULL,       PREC_NONE},
    [TOKEN_MINUS]  = {ParseUnary,  ParseInfix, PREC_TERM},
    [TOKEN_PLUS]   = {NULL,        ParseInfix, PREC_TERM},
    [TOKEN_STAR]   = {NULL,        ParseInfix, PREC_FACTOR},
    [TOKEN_DIVIDE] = {NULL,        ParseInfix, PREC_FACTOR},
};

ParseRule* GetRule(TokenType type) {
    return &rules[type];
}

// --- 2. Node Constructors ---

AST_Expression* MakePrimaryNode(Token tok) {
    AST_Expression* expr = malloc(sizeof(AST_Expression));
    expr->type = PRIMARY;
    strcpy(expr->as.constant.value, tok.lexeme);
    return expr;
}

AST_Expression* MakeBinaryNode(OperationType op, AST_Expression* left, AST_Expression* right){
    AST_Expression* expr = malloc(sizeof(AST_Expression));
    expr->type = BINARY;
    expr->as.binary.type = op;
    expr->as.binary.left_node = left;
    expr->as.binary.right_node = right;
    return expr;
}

OperationType TokenToBinaryOp(Token tok){
    switch (tok.type) {
        case TOKEN_PLUS:  return OP_ADD;
        case TOKEN_MINUS: return OP_MINUS;
        case TOKEN_STAR:  return OP_MUL;
        default:
            fprintf(stderr, " Expected operation, got '%s'\n", tok.lexeme);
            return OP_NONE;
    }
}

// --- 3. Prefix & Infix Parsers ---

AST_Expression* ParseNumber(Parser* parser) {
    AST_Expression* expr = MakePrimaryNode(parser->current_token);
    ParserAdvance(parser);
    return expr;
}

AST_Expression* ParseUnary(Parser* parser) {
    ParserAdvance(parser); // consume operator 
    AST_Expression* right = ParseExpressionPrec(parser, PREC_UNARY);
    
    AST_Expression* expr = malloc(sizeof(AST_Expression));
    expr->type = UNARY;
    expr->as.unary.type = OP_NEG;
    expr->as.unary.node = right;
    return expr;
}

AST_Expression* ParseInfix(Parser* parser, AST_Expression* left){
    Token op_token = parser->current_token;
    Precedence op_prec = GetRule(op_token.type)->precedence;
    ParserAdvance(parser);

    AST_Expression* right = ParseExpressionPrec(parser, op_prec);
    return MakeBinaryNode(TokenToBinaryOp(op_token), left, right);
}

// --- 4. The Core Parsing Engine ---

AST_Expression* ParseExpressionPrec(Parser* parser, Precedence precedence){
    // 1. Look up the prefix rule for the current token
    ParsePrefixFn prefixRule = GetRule(parser->current_token.type)->prefix;

    if (prefixRule == NULL) {
        fprintf(stderr, "Syntax Error, Expected expression, got '%s'\n", parser->current_token.lexeme);
        exit(1);
        return NULL;
    }

    // 2. Execute it to get the left-hand side
    AST_Expression* left = prefixRule(parser);

    // 3. Keep parsing as long as the next token has a higher precedence
    while (precedence < GetRule(parser->current_token.type)->precedence) {
        ParseInfixFn infixRule = GetRule(parser->current_token.type)->infix;
        left = infixRule(parser, left);
    }

    return left;
}

AST_Expression* ParseExpression(Parser* parser){
    return ParseExpressionPrec(parser, PREC_NONE);
}

// --- 5. Debug Utilities ---

const char* GetOpString(OperationType op) {
    switch (op) {
        case OP_ADD:   return "+";
        case OP_MINUS: return "-";
        case OP_MUL:   return "*";
        case OP_NEG:   return "- (unary)";
        case OP_NONE:  return "NONE";
        default:       return "?";
    }
}

void PrintAST(AST_Expression* expr, int depth) {
    if (expr == NULL) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        printf("  "); 
    }

    switch (expr->type) {
        case PRIMARY:
            printf("Constant: %s\n", expr->as.constant.value);
            break;
            
        case UNARY:
            printf("Unary: %s\n", GetOpString(expr->as.unary.type));
            PrintAST(expr->as.unary.node, depth + 1); 
            break;
            
        case BINARY:
            printf("Binary: %s\n", GetOpString(expr->as.binary.type));
            PrintAST(expr->as.binary.left_node, depth + 1);
            PrintAST(expr->as.binary.right_node, depth + 1);
            break;

        case TERNARY:
            printf("Ternary: %s\n", GetOpString(expr->as.ternary.type));
            PrintAST(expr->as.ternary.first_node, depth + 1);
            PrintAST(expr->as.ternary.second_node, depth + 1);
            PrintAST(expr->as.ternary.third_node, depth + 1);
            break;
            
        default:
            printf("Unknown AST Node Type\n");
            break;
    }
}

void DebugPrintAST(AST_Expression* expr) {
    printf("--- AST Dump ---\n");
    PrintAST(expr, 0);
    printf("----------------\n");
}
