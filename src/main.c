#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "parser_util.h"

char* ReadFileToString(const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		fprintf(stderr, "Error: Could not open file '%s'\n", filename);
		return NULL; // Return NULL if the file doesn't exist
	}

	fseek(file, 0, SEEK_END);
	long file_size = ftell(file);

	rewind(file);

	char* buffer = (char*)malloc(file_size + 1);
	if (buffer == NULL) {
		fprintf(stderr, "Error: Not enough memory to read '%s'\n", filename);
		fclose(file);
		return NULL;
	}

	size_t bytes_read = fread(buffer, sizeof(char), file_size, file);

	buffer[bytes_read] = '\0';

	fclose(file);
	return buffer;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <filename.txt>\n", argv[0]);
		return 1;
	}

	const char* filename = argv[1];
	char* source_code = ReadFileToString(filename);

	if (source_code == NULL) {
		return 1; 
	}

	Lexer lexer;
	LexerInit(&lexer, source_code);

	Parser parser;
	ParserInit(&parser, &lexer);
	
	ParseExpression(&parser);
	Compiler compiler;
	InitCompiler(&compiler);
	
	ParseFile(&compiler, &parser);
	
	printf("structures: %d\n",compiler.structure_count);
	printf("functions: %d\n",compiler.function_count);

	PrintCompilerDebug(&compiler);
	free(source_code);

	return 0;
}
