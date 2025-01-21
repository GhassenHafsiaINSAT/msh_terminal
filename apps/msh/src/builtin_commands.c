#include "builtin_commands.h"

void builtin_exit(char **args){

}
void builtin_cd(char **args){

} 
void builtin_echo(char **args){

} 

BuiltinCommands builtins[] = {
	{"cd", builtin_cd}, 
	{"echo", builtin_echo}, 
	{"exit", builtin_exit}
}; 
