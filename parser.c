#include "parser.h"
#include "hashdict.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define check(expression,error) if ((expression)==0){printf(error); return 0;}

void skip_blank(char **buffer){
	while(isspace(**buffer)) {
		*buffer+=buffer_byte;
	}
}

int parse_character(char **buffer, char c){
	if (**buffer!=c){
		return 0;
	}else{
		*buffer += buffer_byte;
		return 1;
	}
}

int parse_word(char **buffer, const char *word) {
	int i = 0;

	//is it the same word?
	while (word[i] != '\0') {
		if ((*buffer)[i] != word[i]) {
			return 0;
		}
		i++;
	}
	
	//ensure it is not a sub word, "hello"!="hellow"
	if (isalpha((unsigned char)(*buffer)[i])) {
		return 0;
	}
	
	//only advance when all word match, we need this for multiple word selection
	*buffer += i*buffer_byte;  
	return 1;
}

int parse_identifier(char **buffer, char *identifier){
	int i = 0;
	while (isalpha((unsigned char)(*buffer)[i])){
		i++;
	}
	if (i==0){
		return 0;
	}
	memcpy(identifier, *buffer, i*buffer_byte);
	identifier[i] = '\0';
	*buffer += i*buffer_byte;  
	return 1;
}

int parse_file(char **buffer, struct dictionary* dic){
	//every file must begin with module:
	check(parse_module(buffer, dic), "every file should begin with \"module\"");
	return 1;
}

int parse_module(char **buffer, struct dictionary* dic){
	skip_blank(buffer);
	int success = 0;
	success = parse_word(buffer,"module");
	if (success == 0){ return 0;}
	skip_blank(buffer);
	char module_name[100];
	check(parse_identifier(buffer, module_name),"module must have name \n");
	dic_add(dic , module_name, strlen(module_name));
	*dic->value = (Identifier){type:MODULE};
}

int open_file(const char* filename, char* buffer) {
    FILE *file = fopen(filename, "r");
    if (!file) return -1;
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (size >= 1024 * 1024) { // 1MB limit for fixed buffer
        fclose(file);
        return -2; 
    }
    
    size_t bytes_read = fread(buffer, 1, size, file);
    buffer[bytes_read] = '\0';
    fclose(file);
    return (int)bytes_read;
}
