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

extern env_var* var_list;

char* get_env_var(char* name); 
void set_env_var(char* name, char* value, bool exported); 
void unset_en_var(char* name); 

#endif