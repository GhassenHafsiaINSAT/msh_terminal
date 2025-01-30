#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

char** identify_pipe(char* input); 
void execute_pipeline(int num_commands); 