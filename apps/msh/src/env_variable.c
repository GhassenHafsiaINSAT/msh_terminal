#include "env_variable.h"

int PS1 = 0;                
char *PS1_content = NULL;
env_var* var_list = NULL;
char* get_env_var(char* name){
	
	if(var_list == NULL){
		printf("the environment variable list is empty"); 
		return NULL; 
	}

	env_var* checker = var_list; 

	while (checker!=NULL){
		if (checker->name == name){
			return checker->value;  
		}
	}

	return NULL; 

	}
void set_env_var(char* name, char* value, bool exported){

	// checking if the variable already exists
	env_var* checker = var_list; 
	while (checker!=NULL){
		if (checker->name == name){
			checker->value = value; 
			checker->exported = exported; 
		}
	}

	// if not, we create one
	// creating a new node
	env_var* new_var = malloc(sizeof(env_var)); 
	new_var->name = name; 
	new_var->value = value;
	new_var->exported = exported;  
	new_var->next = NULL;

	// if the list is already empty
	if(var_list == NULL){
		var_list = new_var;
		return; 
	}  
	// else 
	env_var* last = var_list; 
	while (last->next != NULL){
		last = last->next; 	
	}
		last->next = new_var;

	if (strcmp(name, "PS1")){
		PS1 = 1; 
		PS1_content = value; 
	}
} 

void unset_en_var(char* name){
	env_var* runner = var_list; 
	env_var* previous = NULL; 
	while(runner!=NULL && strcmp(runner->name, name) != 0){
		previous = runner; 
		runner = runner->next; 
	}
	
	// if variable name not found
	if(runner == NULL) {
		fprintf(stderr, "Environment Variable Unkown\n");
		return; 
	}

	// if variable name found in the head of the linked list
	if (previous == NULL){
		var_list = runner->next; 
	}

	// elsewhere 
	else {
		previous->next = runner->next; 
	}

	free(runner); 
}
