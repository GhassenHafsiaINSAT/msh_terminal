#ifndef PARSER_H
#define PARSER_H

#include <string.h>
#include <unistd.h>

#define TOKEN_MAX 3
char *trim_spaces(char *buffer); 
void parse_input(char **buffer);

#endif