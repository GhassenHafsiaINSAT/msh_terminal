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