#ifndef ENV_VARIABLES_H
#define ENV_VARIABLES_H

#include <stdio.h>
#include <stdbool.h>

bool handle_env_variable_PS1(char *buffer); 


typedef struct environment_variables{
    char *name; 
    char *value; 
    struct node* next; 
} env_var; 


void set_env_var(char* name, char* value); 

#endif