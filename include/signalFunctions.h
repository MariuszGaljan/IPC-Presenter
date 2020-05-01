#ifndef SIGNAL_FUNCTIONS_H
#define SIGNAL_FUNCTIONS_H

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include "IPC.h"

__pid_t processes[NUMBER_OF_PROCCESSES];

int pauseWork;

void setSignalReactions();

#endif