#include "job_control.h"

bg_list* jobs_list = NULL; 

void list_jobs(bg_list* bg){
    
    if(bg == NULL) printf("\n"); 
    bg_list* runner = bg; 
    int i = 1; 
    while(bg != NULL){ 
        printf("[%d] %d %s %s", i , runner->process_id, runner->status, runner->command); 
        i++; 
        runner = runner->next; 
    }
}

bool is_background(char* input){
    
    int i = 0; 
    
    while (input[i] != '\0'){
        i++; 
    }
    
    if (input[i] == '&'){
        return true; 
    } 
    
    return false; 
}

void check_job_status(bg_list* job) {

    int status;
    
    // WHOHANG returns 0 if child process still running 
    // it returns 0 immediatly instead of waiting until the process is terminated 
    // WUNTRACED returns if child process is stopped 
    // without these flags, waitpid does return only is the child process is terminated 
    // these returns are evaluated with Status Analysis Macros 

    pid_t pid = waitpid(job->process_id, &status, WNOHANG | WUNTRACED);  

    if (pid > 0) {
        if (WIFEXITED(status)) {                // terminated normally 
            strcpy(job->status, "Terminated");
        } else if (WIFSTOPPED(status)) {        // SIGSTOP signal 
            strcpy(job->status, "Stopped");
        } else if (WIFSIGNALED(status)) {       // SIGINT signal 
            strcpy(job->status, "terminated");
        }
    } else if (pid == 0) {
        strcpy(job->status, "Running");         
    } 
}

void add_job(bg_list* bg, char* job_id, int process_id, char* command, char* status){
    
    bg_list* new_job = malloc(sizeof(bg_list)); 
    new_job->command = command; 
    new_job->job_id = job_id; 
    new_job->process_id = process_id; 
    new_job->status = status; 

    if (bg == NULL) bg = new_job;  
    bg_list* runner = bg; 
    
    while (runner->next != NULL)
        runner = runner->next; 
    
    runner->next = new_job; 
}