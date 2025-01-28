#include <stdio.h>
#include <string.h>
#include "shell_parser.h"
#include "env_variable.h"
#include "handle_commands.h"
#include "job_control.h"

int main(void){

	char buffer[BUFFER_SIZE]; 
	while(1){

		if (PS1){
			printf("%s", PS1_content); 
		}
		else{
			printf("msh>"); 
		}
		fgets(buffer, sizeof(buffer), stdin); 
		void check_job_status(bg_list* job);
	}
}	



