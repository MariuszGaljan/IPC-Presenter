#include "../include/signalFunctions.h"

void pauseWorking() {
    printf("Program work paused.\n");
    pauseWork = 1;
}


void restartWorking() {
    printf("Program work restarted.\n");
    pauseWork = 0;
}


void finishWorking() {
    printf("# Program work finished.\n");
    detachSharedMemory();
    detachSignalSharedMemory();

    if (getpid() == processes[3]) {
        printf("# Releasing resources.\n");
        deleteResources();
    }

    exit(0);
}


void reactToSignal(int sigId) {
    switch (sigId)
    {
    case SIGUSR2:
        pauseWorking();
        break;
    case SIGCONT:
        restartWorking();
        break;
    case SIGINT:
        finishWorking();
        break;
    default:
        break;
    }
}


void receiveSignalFromProcess(int sigUsr1) {
    blockSignalSemaphore(1);
    int sigId = *signalSharedMemory;
    unlockSignalSemaphore(1);

    reactToSignal(sigId);
}


void receiveSignalFromUser(int sigId) {
    blockSignalSemaphore(0);
    *signalSharedMemory = sigId;
    
    int i;
    for (i = 0; i < NUMBER_OF_PROCCESSES; i++) {
        if (processes[i] != getpid()) {
            kill(processes[i], SIGUSR1);
            unlockSignalSemaphore(1);
        }
    }

    unlockSignalSemaphore(0);
    reactToSignal(sigId);
}


void setSignalReactions() {
    pauseWork = 0;
    signal(SIGUSR2, receiveSignalFromUser);
    signal(SIGCONT, receiveSignalFromUser);
    signal(SIGINT, receiveSignalFromUser);
    signal(SIGUSR1, receiveSignalFromProcess);
}
