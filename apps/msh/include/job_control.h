#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <stdbool.h>

typedef struct background_process bg_list; 

typedef struct background_process{
    
    int job_id; 
    pid_t process_id; 
    char* command; 
    char* status; 
    bg_list* next; 
}  bg_list;

extern bg_list* jobs_list; 

void list_jobs(bg_list* bg); 

void add_job(bg_list* bg, int job_id, int process_id, char* command, char* status); 

void check_job_status(bg_list* job); 

bool is_background(char* input); 