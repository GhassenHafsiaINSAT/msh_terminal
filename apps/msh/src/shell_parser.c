#include "shell_parser.h"
#include "handle_commands.h"

char *trim_spaces(char *buffer){
	
	char **arg; 
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
	return buffer; 
}


char **split_command(char *buffer){
	char *tokens[TOKEN_MAX]; 
	char *token = strtok(buffer, ' '); 
	int token_count = 0; 

	while (token != NULL && token_count<TOKEN_MAX)
	{
		tokens[token_count] = token;
		token_count++; 
		token = strtok(NULL, ' '); 
	}
	return tokens; 
}
