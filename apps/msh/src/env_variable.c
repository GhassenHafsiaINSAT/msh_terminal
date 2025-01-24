#include "env_variable.h"

bool handle_env_variable_PS1(char *buffer){

	char variable[20], value[20]; 
	int start = 0; 

	while (buffer[start] == ' '){
		start++; 
	}
	int j = 0; 

	memmove(buffer, buffer + start, strlen(buffer) - start +1); 

	char *equal = strchr(buffer, '='); 
	if (equal == NULL) return false; 
	if ((*(equal + 1) == ' ') || (*(equal - 1) == ' ')) return false; 
	
	*equal = '\0'; 
	strncpy(variable, buffer, sizeof(variable) - 1); 
	variable[sizeof(variable) - 1] = '\0'; 
	strncpy(value, equal +1 ,sizeof(value) - 1); 
	value[sizeof(value) - 1] = '\0'; 
	
	if (strncmp(variable, "PS1\0", 4) == 0) return true;
	
	return false; 
} 

void set_env_var(env_var** head_ref, char* name, char* value, bool exported){
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
