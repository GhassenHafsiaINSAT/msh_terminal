#ifndef HANDLE_SIGNAL_H
#define HANDLE_SIGNAL_H

#include <signal.h>
#include <stdio.h>
#include "handle_input.h"

void sigint_handler(int signum); 
void sigstp_handler(int signum); 

#endif