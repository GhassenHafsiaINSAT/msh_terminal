#ifndef ENV_VARIABLES_H
#define ENV_VARIABLES_H

#include <stdio.h>
#include <stdbool.h>

bool handle_env_variable_PS1(char *buffer); 

extern int PS1 = 0; 
extern char *PS1_content;

typedef struct environment_variables{
    char *name; 
    char *value; 
    bool exported; 
    struct node* next; 
} env_var; 

env_var var_list; 

void set_env_var(env_var** head_ref, char* name, char* value, bool exported); 

#endif