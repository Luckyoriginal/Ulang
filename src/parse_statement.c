#include <stdbool.h>
#include "parse_statement.h"
#include "parse_expression.h"
#include "ast.h"
#include "compiler.h"
#include "lexer.h"
#include "parser.h"

unsigned int ParseStatement(Parser* parser, Compiler* c){
	return ParseAssignement(parser, c); //just this for now
}

unsigned int ParseAssignement(Parser*parser, Compiler* c){
	ParserMatch(parser, TOKEN_IDENTIFIER, "expected identifier"); //statement always start with an identifier
	unsigned int id_variable = ParseVariable(parser, c); //it always start with a variable/function
	if (c->AST_Tree[id_variable].as.variable.is_function){
		ParserConsume(parser, TOKEN_SEMICOLON, "expected ';'");
		return id_variable; //it is just calling a standalone function
	}else{
		unsigned int id = NewNode(c);
		if (ParserCheckConsume(parser, TOKEN_EQUAL)){ //if it is equality variable = expression;
			c->AST_Tree[id].type = AST_StatementEqual;
			c->AST_Tree[id].as.statement_equal.left = id_variable;
			unsigned int right_node = ParseExpression(parser, c);
			c->AST_Tree[id].as.statement_equal.right = right_node;
			ParserConsume(parser, TOKEN_SEMICOLON, "expected ';'");
		}else{
			ParserReportError(parser, "Statement expected");
		}
		return id;
	}
}

unsigned int ParseBlock(Parser*parser, Compiler* c){
	ParserConsume(parser, TOKEN_LBRACKET, "expected '{'"); // block start with a '{'
	unsigned int head_id =-1;
	unsigned int current_id =-1;
	while(!ParserCheck(parser , TOKEN_RBRACKET) && !ParserCheck(parser, TOKEN_EOF)){
		unsigned int new_id = NewNode(c);
		c->AST_Tree[new_id].type = AST_Block;
		unsigned int stmt_id = ParseStatement(parser,c);
		c->AST_Tree[new_id].as.block.statement = stmt_id;
		c->AST_Tree[new_id].as.block.next= -1;

		if (head_id == -1){
			head_id = new_id;
		}else{
			c->AST_Tree[current_id].as.block.next = new_id;
		}
		current_id = new_id;
	}
	ParserConsume(parser, TOKEN_RBRACKET, "expected '}'");
	return head_id;
}
