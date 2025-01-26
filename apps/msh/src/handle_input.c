#include "handle_commands.h"
#include "shell_parser.h"
#include "env_variable.h"

pid_t foreground_pid = -1;

void handle_input(char *buffer){
	
	int start = 0; 
	char** tokens; 
	while (buffer[start] == ' '){
		start++; 
	}

	memmove(buffer, buffer + start, strlen(buffer) - start +1); 
	
	int command_found = 0;
	char* first_word = catch_first_word(buffer); 
	
	// checking if it a builtin command
	for (int i=0; i<NUM_BUILTIN; i++){
		if (strcmp(first_word, builtins[i].name) == 0) {
			//trim spaces
			char* valid_input = trim_spaces(buffer); 
			//splitting the input
			tokens = split_command(valid_input); 
			builtins[i].func(tokens);
			command_found = 1;  
			return; 
		}
	}

	// If it is not builtin command, check if it is external command
	if (!command_found){
		pid_t pid = fork(); 
		
		if (pid == 0){
			
			if (execvp(tokens[0],tokens) == -1){ 
				command_found = 0; 
				return; 
			} 
		}	
		
		else if (pid > 0){
			foreground_pid = pid; 
			waitpid(pid, NULL, 0); 
			command_found = 1; 
			foreground_pid = -1; 
			return; 
		}
		
		else {
		
			fprintf(stderr, "Error while forking");  
			return; 		
		} 
	}

	// check if it is direct assignment
	char *equal_sign = equal_sign_check(tokens[0]); 
	if ( equal_sign != NULL && tokens[1] == NULL){
		char** name_value = extract_var_name_val(equal_sign, tokens[0]);
		set_env_var(&var_list, name_value[0], name_value[1], false); 
		command_found = 1; 
		return; 
	}

	if (!command_found){
		fprintf (stderr, "%s: Command Not Found", tokens[0]);
		return; 
	}


}