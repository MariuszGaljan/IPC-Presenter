#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>

#include "../include/signalFunctions.h"
#include "../include/IPC.h"


int main() {
    int i;
    initSharedMemory();
    initSemaphores();

    // writing process PID to the shared memory
    blockSemaphore(3);
    sharedMemory[3] = getpid();
    unlockSemaphore(0);

    // reading PID values of other processes
    blockSemaphore(0);
    for (i = 0; i < NUMBER_OF_PROCCESSES; i++)
        processes[i] = sharedMemory[i];
    unlockSemaphore(0);

    printf("Other proccesses PIDs:\n");
    for (i = 0; i < NUMBER_OF_PROCCESSES; i++)
        printf("%d\n", processes[i]);
    printf("\n");


    initSignalSharedMemory();
    initSignalSemaphores();

    setSignalReactions();



// project part 1
    key_t msgQueueKey = ftok("msgQueue", 65);
    msgQueue = msgget(msgQueueKey, 0666 | IPC_CREAT);

    struct messageInt msgReceived;
    long numberOfSigns;

    while(1) {
        if (pauseWork)
            pause();
        
        printf("# Waiting for a message.\n");
        msgrcv(msgQueue, &msgReceived, sizeof(struct messageString), 2, 0);
        numberOfSigns = msgReceived.message;

        if (numberOfSigns == -1) {
            printf("## Work finished.\n");
        } else
            printf("Number of signs: %ld\n", numberOfSigns);
    }

    return 0;
}