#include "../include/IPC.h"

// ==================================================== semaphores =========================================================


void initSemaphores() {
    key_t semaphoreKey;
    semaphoreKey = ftok("sem", 65);
    semaphores = semget(semaphoreKey, NUMBER_OF_PROCCESSES, 0660 | IPC_CREAT);
}

// structs used to define the lock and release operations on semaphores for C semop function
struct sembuf semaphoreBlocking = {0, -1, 0};
struct sembuf semaphoreUnlocking = {0, 1, 0};

// procedure blocking the semaphore semNumber in set semaphores
void blockSemaphore(int semNumber) {
    semaphoreBlocking.sem_num = semNumber;
    semop(semaphores, &semaphoreBlocking, 1);
}

// procedure unlocking the semaphore semNumber in set semaphores
void unlockSemaphore(int numerSemafora) {
    semaphoreUnlocking.sem_num = numerSemafora;
    semop(semaphores, &semaphoreUnlocking, 1);
}



// ================================================ shared memory =========================================================

int shmId;

void initSharedMemory() {
    __key_t key;
    key = ftok("shm_file", 65);
    shmId = shmget(key, NUMBER_OF_PROCCESSES * sizeof(pid_t), 0666|IPC_CREAT);
    sharedMemory = (pid_t*) shmat(shmId, 0, 0);
}

void detachSharedMemory() {
    shmdt(sharedMemory);
}


// ================================================ signal IPC ========================================================

// semaphores

void initSignalSemaphores() {
    key_t semKey;
    semKey = ftok("semSig", 66);
    signalSemaphores = semget(semKey, NUMBER_OF_PROCCESSES, 0660 | IPC_CREAT);
}

void blockSignalSemaphore(int semNumber) {
    semaphoreBlocking.sem_num = semNumber;
    semop(signalSemaphores, &semaphoreBlocking, 1);
}

void unlockSignalSemaphore(int semNumber) {
    semaphoreUnlocking.sem_num = semNumber;
    semop(signalSemaphores, &semaphoreUnlocking, 1);
}


// signals shared memory

int shmSigId;

void initSignalSharedMemory() {
    __key_t key;
    key = ftok("shmSig_file", 66);
    shmId = shmget(key, sizeof(int), 0666|IPC_CREAT);
    signalSharedMemory = (int *) shmat(shmId, 0, 0);
}

void detachSignalSharedMemory() {
    shmdt(signalSharedMemory);
}


void deleteResources() {
    printf("# Releasing resources.\n");
    semctl(semaphores, 0, IPC_RMID, NULL);
    semctl(signalSemaphores, 0, IPC_RMID, NULL);
    shmctl(shmId, IPC_RMID, NULL);
    shmctl(shmSigId, IPC_RMID, NULL);
    msgctl(msgQueue, IPC_RMID, NULL);
    printf("# Releasing resources finished.\n");

}
