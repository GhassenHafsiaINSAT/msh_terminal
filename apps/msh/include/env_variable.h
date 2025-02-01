#ifndef ENV_VARIABLES_H
#define ENV_VARIABLES_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

extern int PS1; 
extern char *PS1_content;

typedef struct environment_variables{
    char *name; 
    char *value; 
    bool exported; 
    struct environment_variables* next; 
} env_var; 

env_var* var_list = NULL;

void set_env_var(env_var* head_ref, char* name, char* value, bool exported); 
void unset_en_var(env_var* head_ref, char* name); 
#endif