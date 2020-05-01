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
    blockSemaphore(2);
    sharedMemory[2] = getpid();
    unlockSemaphore(3);

    // reading PID values of other processes
    blockSemaphore(0);
    for (i = 0; i < NUMBER_OF_PROCCESSES; i++)
        processes[i] = sharedMemory[i];
    unlockSemaphore(0);
    
    printf("Other processes' PIDs\n");
    for (i = 0; i < NUMBER_OF_PROCCESSES; i++)
        printf("%d\n", processes[i]);
    printf("\n");

    initSignalSharedMemory();
    initSignalSemaphores();

    setSignalReactions();



// project part 1
    key_t msgQueueKey = ftok("msgQueue", 65);
    msgQueue = msgget(msgQueueKey, 0666 | IPC_CREAT);

    struct messageString msgReceived;
    
    struct messageInt msgSent;
    msgSent.messageType = 2;

    long numberOfChars;

    while (1) {
        if (pauseWork)
            pause();
        
        printf("# Waiting for a message.\n");
        msgrcv(msgQueue, &msgReceived, sizeof(struct messageString), 1, 0);
        printf("Message received:\n %s", msgReceived.message);

        numberOfChars = 0;
        while (msgReceived.message[numberOfChars] != '\n' && msgReceived.message[numberOfChars] != '\0')
            numberOfChars++;

        printf("# Sending message\n");
        
        // sending the message with the number of characters in string
        msgSent.message = numberOfChars;
        msgsnd(msgQueue, &msgSent, sizeof(msgSent), IPC_NOWAIT);
    }

    detachSharedMemory();
    detachSignalSharedMemory();

    printf("# Work finished.\n");
    return 0;
}