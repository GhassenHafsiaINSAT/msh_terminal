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

char** extract_var_name_val(char *equal, char* buffer) {    
    *equal = '\0'; 

    char *variable = malloc(strlen(buffer) + 1); 
    char *value = malloc(strlen(equal + 1) + 1); 

    strcpy(variable, buffer); 
    strcpy(value, equal + 1); 

    char **result = malloc(2 * sizeof(char*)); 

    result[0] = variable;
    result[1] = value;
    return result;
}

char* equal_sign_check(char* buffer){
	
	char *equal = strchr(buffer, '='); 
	if (equal != NULL){
		if ((*(equal + 1) == ' ') || (*(equal - 1) == ' ')){
			fprintf(stderr, "Invalid Syntax <a>=<b>"); 
			return NULL; 
		}
		return equal; 
	}
	return NULL;  

}
char* catch_first_word(char *buffer){

	char* first_word; 
	int i = 0; 
	
	while((buffer[i] != ' ') || (buffer[i] != '\0')){
		first_word[i] = buffer[i]; 
		i++; 
	}
	first_word[i] = '\0'; 
}