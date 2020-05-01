#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <string.h>

#include "../include/signalFunctions.h"
#include "../include/IPC.h"


int main() {
    int i;
    initSharedMemory();
    initSemaphores();

    // writing process PID to the shared memory
    blockSemaphore(1);
    sharedMemory[1] = getpid();
    unlockSemaphore(2);

    // reading PID values of other processes
    blockSemaphore(0);
    for (i = 0; i < NUMBER_OF_PROCCESSES; i++)
        processes[i] = sharedMemory[i];
    unlockSemaphore(0);
    
    printf("Other processes' PIDs:\n");
    for (i = 0; i < NUMBER_OF_PROCCESSES; i++)
        printf("%d\n", processes[i]);
    printf("\n");

    initSignalSharedMemory();
    initSignalSemaphores();

    setSignalReactions();


// project part 1
    // int exitOccurred = 0;
    key_t msgQueueKey = ftok("msgQueue", 65);
    msgQueue = msgget(msgQueueKey, 0666 | IPC_CREAT);

    struct messageString msgString;
    msgString.messageType = 1;
    memset(&(msgString.message), 0, BUFFER_SIZE * sizeof(char));

    while (1) {
        if (pauseWork)
            pause();
        
        printf("# Enter text:\n");
        fgets(msgString.message, BUFFER_SIZE, stdin);
        printf("Text entered:\n%s", msgString.message);

        // sending the unprocessed text
        msgsnd(msgQueue, &msgString, sizeof(msgString), 0);
    }

    return 0;
}