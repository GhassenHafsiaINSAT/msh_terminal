#include <stdio.h>
#include <string.h>
#include "shell_parser.h"
#include "env_variable.h"
#include "handle_commands.h"


int main(void){

	char buffer[1024]; 

	while(1){
		printf("miniShell@ghassen-hafsia>"); 
		fgets(buffer, sizeof(buffer), stdin); 
		trim_spaces(buffer);
	}
}	



