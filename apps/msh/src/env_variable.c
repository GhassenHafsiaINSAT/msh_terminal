#include "env_variable.h"

void set_env_var(env_var** head_ref, char* name, char* value, bool exported){
	// checking if the variable already exists
	env_var* checker = *head_ref; 
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
	env_var* last = *head_ref; 
	if(head_ref == NULL){
		head_ref = new_var;
		return; 
	}  
	// else 
	while (last->next != NULL){
		last = last->next; 	
	}
		last->next = new_var;

	if (strcmp(name, "PS1")){
		PS1 = 1; 
		PS1_content = value; 
	}
} 

void unset_en_var(env_var** head_ref, char* name){
	env_var* runner = *head_ref; 
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
		*head_ref = runner->next; 
	}
	// elsewhere 
	else {
		previous->next = runner->next; 
	}

	free(runner); 
}
