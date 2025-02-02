#include "handle_commands.h"
#include "shell_parser.h"
#include "env_variable.h"

extern pid_t foreground_pid;

int execute_builtin(char** tokens, char* first_word);
int execute_external(char** tokens);
int execute_direct_assignment(char** tokens);
int handle_input(char *buffer); 