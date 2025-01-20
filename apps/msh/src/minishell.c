#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void trim_spaces(char *buffer); 
bool handle_env_variable_PS1(char *buffer); 

int main(void){

	char buffer[1024]; 

	while(1){
		printf("miniShell@ghassen-hafsia>"); 
		fgets(buffer, sizeof(buffer), stdin); 
		trim_spaces(buffer);
	}
}	

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

void trim_spaces(char *buffer){
	
	int end = strlen(buffer) - 1; 


	while ((end) && (buffer[end] == ' ')){
		end --; 
	}
	int j = 0; 

	buffer[end + 1] = '\0';

	j = 0;
	int space_found = 0;  
	for (int i = 0; buffer[i] != '\0'; i++) {
			if (buffer[i] == ' ') {
				if (space_found) {
					continue;
				}
				space_found = 1; 
			} else {
				space_found = 0; 
			}
			buffer[j++] = buffer[i]; 
		}

	buffer[j] = '\0';
}