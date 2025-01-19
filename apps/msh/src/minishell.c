#include <stdio.h>
#include <string.h>

void trim_spaces(char *buffer); 

int main(void){
	
	char buffer[1024]; 

	while(1){
		printf("miniShell@ghassen-hafsia>"); 
		fgets(buffer, sizeof(buffer), stdin); 
		trim_spaces(buffer);
		// printf("test :%s\n", buffer);  
	}
}	


void trim_spaces(char *buffer){
	
	int start = 0;
	int end = strlen(buffer) - 1; 

	while (buffer[start] == ' '){
		start++; 
	}

	while ((end > start) && (buffer[end] == ' ')){
		end --; 
	}
	int j = 0; 

	for (int i = start ; i < end; i++){
		buffer[j++] = buffer[i]; 
	}

	buffer[j] = '\0';
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
}