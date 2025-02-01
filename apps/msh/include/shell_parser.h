#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define TOKEN_MAX 3
#define BUFFER_SIZE 1024

char* remove_leading_spaces(char* buffer);
char* trim_spaces(char *buffer); 
char** split_command(char *buffer); 
char* catch_first_word(char *buffer); 
char* equal_sign_check(char* buffer);
char** extract_var_name_val(char *equal, char* buffer);

#endif