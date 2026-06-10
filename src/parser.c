#include "parser.h"
#include "lexer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FIELDS 256 // Ensure you have a limit!
		       //
void ParserInit(Parser *parser, Lexer *lexer){
	parser->lexer = lexer;
	parser->current_token = LexerNextToken(lexer);
}

void ParserAdvance(Parser *parser){
	parser->current_token = LexerNextToken(parser->lexer);
}

bool ParserExpectedToken(Parser *parser, TokenType expected_type, const char* error_msg) {
	if (parser->current_token.type == expected_type) {
		ParserAdvance(parser);
		return true;
	}
	fprintf(stderr, "Syntax Error: %s. Got '%s'\n", error_msg, parser->current_token.lexeme);
	return false;
}

bool ParserMatchAndCopy(Parser *parser, TokenType expected_type, char* dest, const char* error_msg) {
	if (parser->current_token.type == expected_type) {
		strcpy(dest, parser->current_token.lexeme);
		ParserAdvance(parser);
		return true;
	}
	fprintf(stderr, "Syntax Error: %s. Got '%s'\n", error_msg, parser->current_token.lexeme);
	return false;
}

bool ParserCheckAndCopy(Parser *parser, TokenType expected_type, char* dest) {
	if (parser->current_token.type == expected_type) {
		strcpy(dest, parser->current_token.lexeme);
		return true;
	}
	return false;
}

bool ParserParseField(Parser* parser, AST_Field_Declaration* field) {
	if (!ParserMatchAndCopy(parser, TOKEN_IDENTIFIER, field->type_name, "Expected field type")) {
		return false;
	}

	if (!ParserMatchAndCopy(parser, TOKEN_IDENTIFIER, field->field_name, "Expected field name")) {
		return false;
	}

	if (!ParserExpectedToken(parser, TOKEN_SEMICOLON, "Expected ';' after field declaration")) {
		return false;
	}

	return true;
}

bool ParseTypeDefinition(Parser* parser, Compiler* c) {
	//struct_definition->field_count = 0; // Always initialize!
	char name[64];
	if (!ParserMatchAndCopy(parser, TOKEN_IDENTIFIER, name, "Expected name")) return false;

	if (parser->current_token.type == TOKEN_STRUCT){
		ParserAdvance(parser);
		if (!ParserExpectedToken(parser, TOKEN_LPARENTHESIS, "Expected '{' to open struct")) return false;

		while (parser->current_token.type != TOKEN_RPARENTHESIS && parser->current_token.type != TOKEN_EOF) {
			AST_Struct_Definition* struct_definition = &c->structure[c->structure_count];
			strcpy(struct_definition->struct_name,name);
			if (struct_definition->field_count >= MAX_FIELDS) {
				fprintf(stderr, "Compiler Error: Struct '%s' exceeded max fields.\n", struct_definition->struct_name);
				return false;
			}

			if (!ParserParseField(parser, &struct_definition->fields[struct_definition->field_count])) {
				return false; 
			}

			struct_definition->field_count++;
		}

		if (!ParserExpectedToken(parser, TOKEN_RPARENTHESIS, "Expected '}' to close struct")) return false;

		if (c->structure_count<MAX_COUNT){
			c->structure_count++;
		}
		return true;
	}
	return false;
}

bool ParseFunctionField(Parser* parser, Compiler* c) {
	AST_Function_Definition *functions= c->functions;
	if (ParserCheckAndCopy(parser, TOKEN_IDENTIFIER, functions->argument_name[functions->argument_count])){
		ParserAdvance(parser);
		if (!ParserMatchAndCopy(parser , TOKEN_IDENTIFIER,functions->argument_type[functions->argument_count] ,"expected field type")) return false;

		functions->argument_count++;
	}
	while (parser->current_token.type == TOKEN_COMMA){
		ParserAdvance(parser);
		if (!ParserMatchAndCopy(parser, TOKEN_IDENTIFIER,functions->argument_name[functions->argument_count], "expected field name")) return false;
		if (!ParserMatchAndCopy(parser, TOKEN_IDENTIFIER,functions->argument_type[functions->argument_count], "expected field type ")) return false;
		functions->argument_count++;
	}

	return true;
}

bool ParseFunctionDefinition(Parser* parser, Compiler* c) {
	//struct_definition->field_count = 0; // Always initialize!
	ParserAdvance(parser);
	if (!ParserMatchAndCopy(parser, TOKEN_IDENTIFIER, c->functions[c->function_count].function_name, "Expected Function's name")) return false;
	if (!ParserExpectedToken(parser, TOKEN_LBRACKET, "Expected '(' to open function")) return false;
	if (!ParseFunctionField(parser, c)) return false;
	if (!ParserExpectedToken(parser, TOKEN_RBRACKET, "Expected ')' to close function")) return false;

	if (c->structure_count<MAX_COUNT){
		c->function_count++;
	}
	return true;
}

void InitCompiler(Compiler* c){
	c->structure_count=0;
	c->function_count=0;
}

void ParseFile(Compiler* c, Parser* p){
	int i;
	for (i=0;i<4;i++){
		if (p->current_token.type == TOKEN_EOF){ printf("finish\n") ;break;}
		if (p->current_token.type == TOKEN_TYPE){
			ParserAdvance(p);
			ParseTypeDefinition(p, c);
		}
		if (p->current_token.type==TOKEN_FUNC){
			ParseFunctionDefinition(p, c);
		}
	}
	if (i==4){
		printf("infinite loop\n");
	}
}
