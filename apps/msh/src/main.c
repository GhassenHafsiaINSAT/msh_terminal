#include <stdio.h>
#include <string.h>
#include "shell_parser.h"
#include "env_variable.h"
#include "handle_commands.h"


int main(void){

	char buffer[1024]; 
	while(1){

		if (PS1){
			printf("%s", PS1_content); 
		}
		else{
			printf("msh>"); 
		}
		fgets(buffer, sizeof(buffer), stdin); 

	}
}	



