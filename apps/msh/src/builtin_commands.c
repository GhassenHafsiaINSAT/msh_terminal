#include "builtin_commands.h"

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
		printf("%s", args[i]); 
		if (args[i + 1] != NULL) printf(" ");
		i++;  
	}
	if (new_line) printf("\n"); 
} 

void builtin_pwd(char **args){

	char *buf[4096];
	char *path = getcwd(buf, sizeof(buf)); 
	if (path == NULL){
		fprintf(stderr, "Searching for Path is impossible");
		exit(1); 
	}
	printf("%s\n", path); 
}
BuiltinCommands builtins[] = {
	{"cd", builtin_cd}, 
	{"echo", builtin_echo}, 
	{"exit", builtin_exit}, 
	{"pwd", builtin_pwd}
}; 
