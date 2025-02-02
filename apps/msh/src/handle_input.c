#include "handle_input.h"

pid_t foreground_pid = 0; 
int execute_builtin(char** tokens, char* first_word){
	
	for (int i=0; i<NUM_BUILTIN; i++){
		if (strcmp(first_word, builtins[i].name) == 0) {

			builtins[i].func(tokens);
			return 1;  
		}
	}
	
	return 0; 
}

int execute_external(char** tokens){

		pid_t pid = fork(); 
		
		if (pid == 0){

			if (execvp(tokens[0],tokens) == -1){ 
				fprintf(stderr, "execvp failed\n"); 
				exit(1); 
			} 
		}	
		
		else if (pid > 0){
			foreground_pid = pid; 
			waitpid(pid, NULL, 0);
			foreground_pid  = -1;  
			return 1; 
		}
		
		fprintf(stderr, "Error while forking\n");  
		return 0; 		
}

int execute_direct_assignment(char** tokens){
	
	char *equal_sign = equal_sign_check(tokens[0]); 
	
	if ( equal_sign != NULL && tokens[1] == NULL){
		char** name_value = extract_var_name_val(equal_sign, tokens[0]);
		set_env_var(name_value[0], name_value[1], false); 
		return 1; 
	}

	return 0; 
}

int handle_input(char *buffer){
	
	if ((buffer == NULL) || 
		(strlen(buffer) == 0) ||
		(strlen(remove_leading_spaces(buffer)) == 0)
		){

		printf("\n"); 
		return 0; 
	}

	int command_found = 0; 
	char* target = strdup(buffer); 
	
	if (target == NULL){
		fprintf(stderr, "Error while forking the user input");  
		return 1;
	} 

	// starting with removing leading spaces
	target = remove_leading_spaces(target); 

	// checking for the first word 
	char* first_word = catch_first_word(target); 
	
	//trim spaces
	target = trim_spaces(target); 

	//splitting the input
	char** tokens = split_command(target); 

	// If it is builtin command, execute 
	if ((command_found = execute_builtin(tokens, first_word)) == 1){
		free(target); 
		free(tokens); 
		return 0;  
	}

	// else if it is external command, execute 
	if ((command_found = execute_external(tokens)) == 1){
		free(tokens); 
		free(target); 
		return 0; 
	}

	// else if it is direct assignment, execute 
	if ((command_found = execute_direct_assignment(tokens)) == 1){
		free(tokens); 
		free(target); 
		return 0; 
	}

	// else, show error 
	fprintf (stderr, "%s: Command Not Found\n", tokens[0]);
	free(tokens); 
	free(target); 
	return 1;  
}