#include "handle_commands.h"

void handle_input(char **tokens){
	int i; 
	int status = 0; 

	// Checking if this input is a builtin command 
	for (i=0; i<NUM_BUILTIN; i++){
		if (strcmp(tokens[0], builtins[i].name) == 0) 
			builtins[i].func(tokens);
			status = 1;  
			return; 
	}

	// If it is not builtin command, check if it is external command
	if (!status){
		pid_t pid = fork(); 
		if (pid == 0){
			
			if (execvp(tokens[0],tokens) == -1){
				fprintf (stderr, "Command Not Found"); 
				exit(1); 
			} 
		}	
		else if (pid > 0){
			waitpid(pid, NULL, 0); 
			status = 1; 
			return; 
		}
		else{
			fprintf(stderr, "Error while forking"); 
			exit(1); 
		} 
	}
}