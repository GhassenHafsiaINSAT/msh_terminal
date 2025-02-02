#include "handle_signal.h"

void sigint_handler(int signum){
    if (foreground_pid > 0){
        kill (foreground_pid, SIGINT); 
    }
}

void sigstp_handler(int signum){
    if (foreground_pid > 0){
        kill(foreground_pid, SIGTSTP); 
    }
}