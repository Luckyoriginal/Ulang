#ifndef PARSER
#define PARSER
#include "hashdict.h"

#define buffer_byte 1 //this is in case we want non UTF-8 file format
//file utility that copy file to buffer
int open_file(const char* filename, char* buffer);

//parsing function base
void skip_blank(char **buffer);
int parse_character(char **buffer, char c);
int parse_word(char **buffer, const char *word);
int parse_identifier(char **buffer, char *identifier);

//parsing function 
int parse_file(char **buffer,struct dictionary* dic);
int parse_module(char **buffer,struct dictionary* dic);
#endif 
