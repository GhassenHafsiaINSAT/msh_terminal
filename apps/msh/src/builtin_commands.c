#include "handle_commands.h"
#include "shell_parser.h"
#include "env_variable.h"
#include "job_control.h"

int exit_status = 0; 

void builtin_exit(char **args){
	
	if(args[1] == NULL) exit(0);
	
	char *endptr; 
	long arg = strtol(args[1], &endptr, 10); 

	if (*endptr != '\0') {
		fprintf(stderr, "No Valid Argument: %s. Exiting with code 1.\n", args[1]); 
		exit(1); 
	}

	if (arg >= 0 && arg <= 255){		 
		exit(arg); 
	} else {
		fprintf(stderr, "Argument out of range: %s. Exiting with code 1.\n", args[1]);
		exit(1);
	}  
	
}

void builtin_cd(char **args){
	if (args[1] == NULL) {
		char *home_path = getenv("HOME");
		if (home_path == NULL){
			printf("cd : Home : home directory not found"); 
			return;
		}
		chdir(home_path);
		return; 
	} 
	char *path = args[1]; 
	int n = access(path,F_OK);
	if (n == 0) {
		chdir(args[1]); 
		return; 
	}
	else {
		fprintf(stderr, "cd : %s : No such file or directory", args[1]);
		return; 
	} 
} 

void builtin_echo(char **args){
	int new_line = 1; 
	int i = 1; 

	if ((args[1] != NULL) && (strcmp(args[1], "-n") == 0)){
		new_line = 0;
		i++; 
	}   
	while (args[i] != NULL){
		
		if (strcmp(args[i], "$?") == 0){
			printf("%d", exit_status); 
		}

		else if (strcmp(args[i], "$$") == 0){
			pid_t caller_id = getpid(); 
			printf("%d", caller_id); 
		}

		else if (strcmp(args[i], "$SHELL") == 0){
			char *path = getenv("SHELL"); 
			printf("%s", path); 
		}

		else {
			printf("%s", args[i]);
		}

		if (args[i + 1] != NULL) printf(" ");
		i++;  
	}
	if (new_line) printf("\n"); 
} 

void builtin_pwd(char **args){

	char *path = getcwd(args[1], sizeof(args[1])); 
	if (path == NULL){
		fprintf(stderr, "Searching for Path is impossible");
		exit(1); 
	}
	printf("%s\n", path); 
}

void builtin_export(char **args){
	
	char* equal = equal_sign_check(args[1]);
	if (equal == NULL) {
		fprintf (stderr, "Wrong Syntax"); 
		exit(1); 
	}
	char **result = extract_var_name_val(equal, args[1]);  
	set_env_var(&var_list, result[0], result[1], true); 

}

void builtin_set(char **args){
	char* equal = equal_sign_check(args[1]);
	if (equal == NULL) {
		fprintf (stderr, "Wrong Syntax"); 
		exit(1); 
	}
	char **result = extract_var_name_val(equal, args[1]);  
	set_env_var(&var_list, result[0], result[1], false); 
}

void builtin_unset(char **args){
	unset_en_var(&var_list, args[1]); 
}

void builtin_jobs(){
	bg_list* runner = jobs_list;
	
	if (runner == NULL) printf ("\n"); 

	while (runner != NULL)
	{
		printf ("[%d] %s %s" , runner->job_id, runner->status, runner->command); 
	}
}

void builtin_bg(char **args){
	bg_list* runner = jobs_list; 
	while(runner != NULL){
		if (runner->job_id == args[1] && runner->status ==  "paused"){
			kill(runner->process_id, SIGCONT);  
            runner->status = "running"; 
			printf("[%d]+ %s %s &", runner->job_id, args[0], args[1]);            
		} 
		runner = runner ->next; 
	}
	    printf("Job [%d] not found or not stopped.\n", runner->job_id);
}

void builtin_fg(char **args){
	
	bg_list* runner = jobs_list; 

	while (runner != NULL){
		if (runner->job_id == args[1]) {

        	pid_t pid = runner->process_id;
            
            tcsetpgrp(STDIN_FILENO, pid);
            
            kill(pid, SIGCONT);

            int status;
            waitpid(pid, &status, WUNTRACED);

            tcsetpgrp(STDIN_FILENO, getpid());
            
            return;
        }
		runner = runner->next; 
	}
    printf("Job [%d] not found.\n", args[1]);

    }

BuiltinCommands builtins[] = {
	{"cd", builtin_cd}, 
	{"echo", builtin_echo}, 
	{"exit", builtin_exit}, 
	{"pwd", builtin_pwd}, 
	{"export", builtin_export},
	{"set", builtin_set},
	{"unset", builtin_unset},
	{"jobs", builtin_jobs}, 
	{"bg", builtin_bg}, 
	{"fg", builtin_fg}
}; 
