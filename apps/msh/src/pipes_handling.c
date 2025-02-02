#include "pipes_handling.h"

char** identify_pipe(char* input){
    
    char* copy = strdup(input);  
    if (!copy) return NULL;
    
    char* pipe = strtok(copy, "|"); 

    if (pipe == NULL) return NULL; 

    char** pipe_process = NULL; 
    int num_pipes = 0; 

    while ( pipe != NULL ) {
        
        char** temp = realloc(pipe_process, (num_pipes + 1) * sizeof(char *));
        if (temp == NULL){
            free(pipe_process); 
            free(temp); 
            return NULL; 
        }
        pipe_process = temp;
        pipe_process[num_pipes] = strdup(pipe); 
        num_pipes++; 
        pipe = strtok (NULL, "|");

    }
    
    char** temp = realloc(pipe_process, (num_pipes + 1) * sizeof(char *)); 
    pipe_process = temp; 
    pipe_process[num_pipes] = NULL; 
    
    free(copy); 
    return pipe_process; 
}

void execute_pipeline(int num_commands){

    int pipefds[2 * (num_commands - 1)];

    for (int i = 0; i < num_commands; ++i) {
        if (i < num_commands - 1) {
            if (pipe(pipefds + 2 * i) == -1) {
                perror("pipe");
                return;
            }
        }    

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            return;
        }
        if (pid == 0) {
            // if it is not the first command, take input from the previous pipe
            if (i > 0) { 
                dup2(pipefds[2 * (i - 1)], STDIN_FILENO);
            }

            // If it's not the last command, send output to next pipe
            if (i < num_commands - 1) {
                dup2(pipefds[2 * i + 1], STDOUT_FILENO);
            }

            // Close all pipe file descriptors
            for (int j = 0; j < 2 * (num_commands - 1); ++j) {
                close(pipefds[j]);
            }
        }
    }

    for (int j = 0; j < 2 * (num_commands - 1); ++j) {
        close(pipefds[j]);
    }

    for (int i = 0; i < num_commands; ++i) {
        wait(NULL);
    }
}
