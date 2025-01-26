#ifndef HANDLE_COMMAND_H
#define HANDLE_COMMAND_H

#include <signal.h>
#include <stdio.h>

void sigint_handler(int signum); 
void sigstp_handler(int signum); 

#endif