#ifndef BUILTIN_COMMANDS_H
#define BUILTIN_COMMANDS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void builtin_exit(char **args);

void builtin_cd(char **args); 

void builtin_echo(char **args); 

void builtin_pwd(char **args); 

#define NUM_BUILTIN 4

typedef struct {
	char *name; 
	void (*func)(char **args); 
} BuiltinCommands; 

extern BuiltinCommands builtins[]; 

#endif
