#ifndef IPC_H
#define IPC_H

#include <stdio.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define NUMBER_OF_PROCCESSES 4

#define BUFFER_SIZE 128


// message queue
int msgQueue;

// we use this struct to pass strings of length <= BUFFER_SIZE via messages
typedef struct messageString {
    long messageType;
    char message[BUFFER_SIZE];
}messageString;

// we use this structs to pass int values via messages
typedef struct messageInt {
    long messageType;
    long message;
}messageInt;


// semaphore pool containing NUMBER_OF_PROCCESSES semaphores
// semaphore 0 - read semaphore which opens when all the proccesses write their PIDs in sharedMemory
int semaphores;

// array of PIDs, size = NUMBER_OF_PROCCESSES
pid_t *sharedMemory; 


void initSemaphores();
void blockSemaphore(int semNumber);
void unlockSemaphore(int semNumber);

void initSharedMemory();
void detachSharedMemory();

// ======================================= IPC sygnalow =====================================

int signalSemaphores;

// a shared integer containing the value of the signal
int *signalSharedMemory;

void initSignalSemaphores();
void blockSignalSemaphore(int semNumber);
void unlockSignalSemaphore(int semNumber);

void initSignalSharedMemory();
void detachSignalSharedMemory();

void deleteResources();

#endif