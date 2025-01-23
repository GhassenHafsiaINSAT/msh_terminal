#include "handle_commands.h"

void handle_input(char **tokens){
	int i; 
	exit_status = 1; 

	// Checking if this input is a builtin command 
	for (i=0; i<NUM_BUILTIN; i++){
		if (strcmp(tokens[0], builtins[i].name) == 0) 
			builtins[i].func(tokens);
			exit_status = 0;  
			return; 
	}

	// If it is not builtin command, check if it is external command
	if (!exit_status){
		pid_t pid = fork(); 
		
		if (pid == 0){
			
			if (execvp(tokens[0],tokens) == -1){
			
				fprintf (stderr, "Command Not Found"); 
				exit_status = 1; 
				return; 
			} 
		}	
		
		else if (pid > 0){
			
			waitpid(pid, NULL, 0); 
			exit_status = 0; 
			return; 
		}
		
		else {
		
			fprintf(stderr, "Error while forking"); 
			exit_status = 1; 
			return; 		
		} 
	}
}