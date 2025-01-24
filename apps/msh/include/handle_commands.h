#ifndef HANDLE_COMMAND_H
#define HANDLE_COMMAND_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

#include "shell_parser.h"
#include "env_variable.h"

extern exit_status; 

void handle_input(char **tokens); 

// Builtin Commands 
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
