#ifndef HANDLE_COMMAND_H
#define HANDLE_COMMAND_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/wait.h>

extern int exit_status; 


// Builtin Commands 
void builtin_exit(char **args);

void builtin_cd(char **args); 

void builtin_echo(char **args); 

void builtin_pwd(char **args); 

void builtin_export(char **args);

void builtin_set(char **args);

void builtin_unset(char **args);

void builtin_jobs(char **args); 

#define NUM_BUILTIN 8

typedef struct {
	char *name; 
	void (*func)(char **args); 
} BuiltinCommands; 

extern BuiltinCommands builtins[]; 

#endif
