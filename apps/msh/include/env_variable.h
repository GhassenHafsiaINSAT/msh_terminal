#ifndef ENV_VARIABLES_H
#define ENV_VARIABLES_H

#include <stdio.h>
#include <stdbool.h>

bool handle_env_variable_PS1(char *buffer); 


typedef struct environment_variables{
    char *name; 
    char *value; 
    bool exported; 
    struct node* next; 
} env_var; 


void set_env_var(env_var** head_ref, char* name, char* value, bool exported); 

#endif