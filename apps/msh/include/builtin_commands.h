#ifndef BUILTIN_COMMANDS_H
#define BUILTIN_COMMANDS_H

void builtin_exit(char **args);

void builtin_cd(char **args); 

void builtin_echo(char **args); 

#define NUM_BUILTIN 3

typedef struct {
	char *name; 
	void (*func)(char **args); 
} BuiltinCommands; 

extern BuiltinCommands builtins[]; 

#endif
