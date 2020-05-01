#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "../include/signalFunctions.h"
#include "../include/IPC.h"

int main() {
    int i;
    char *process1Path;
    char *process2Path;
    char *process3Path;

    // generating absolute paths of the processes
    process1Path = realpath("executable/process1", NULL);
    process2Path = realpath("executable/process2", NULL);
    process3Path = realpath("executable/process3", NULL);

    if (process1Path == NULL || process2Path == NULL || process3Path == NULL) {
        printf("Process executable files missing\n Finishing work.\n");
        return 1;
    }

    initSharedMemory();
    initSemaphores();

    // initializing all semaphores to be locked
    semctl(semaphores, 0, SETVAL, 1);
    semctl(semaphores, 1, SETVAL, -1);
    semctl(semaphores, 2, SETVAL, -1);
    semctl(semaphores, 3, SETVAL, -1);
    blockSemaphore(0);


    // launching processes
    if (fork() == 0) {
        char *args[]={"./scripts/processLaunchScript.sh", process1Path, process2Path, process3Path, NULL};
        execvp(args[0], args);
    }

    // writing process PID to shared memory
    sharedMemory[0] = getpid();
    unlockSemaphore(1);

    // reading PID values of other processes
    blockSemaphore(0);
    for (i = 0; i < NUMBER_OF_PROCCESSES; i++)
        processes[i] = sharedMemory[i];
    unlockSemaphore(0);

    printf("Other processes' PIDs:\n");
    for (i = 0; i < NUMBER_OF_PROCCESSES; i++)
        printf("%d\n", processes[i]);


    initSignalSharedMemory();
    initSignalSemaphores();

    setSignalReactions();

    while(1) {
        if (pauseWork)
            pause();
        
        sleep(1);
    }

    detachSharedMemory();
    detachSignalSharedMemory();
}