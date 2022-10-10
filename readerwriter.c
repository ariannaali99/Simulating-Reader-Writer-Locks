#include "readerwriter.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void rwlock_init(rwlock_t *rw) {
    rw->readers = 0;
    sem_init(&rw->lock, 0, 1);
    sem_init(&rw->writelock, 0, 1);
    sem_init(&rw->orderMutex, 0, 1);
}

void rwlock_acquire_readlock(rwlock_t *rw) {
    sem_wait(&rw->orderMutex);
    sem_wait(&rw->lock);
    sem_post(&rw->orderMutex);
    rw->readers++;
    if(rw->readers == 1) {
        sem_wait(&rw->writelock);
    }
    //sem_post(&rw->orderMutex);
    sem_post(&rw->lock);
}

void rwlock_release_readlock(rwlock_t *rw) {
    sem_wait(&rw->lock);
    rw->readers--;
    if(rw->readers == 0) {
        sem_post(&rw->writelock);
    }
    sem_post(&rw->lock);
}

void rwlock_acquire_writelock(rwlock_t *rw) {
    sem_wait(&rw->orderMutex);
    sem_wait(&rw->writelock);
    sem_post(&rw->orderMutex);
}

void rwlock_release_writelock(rwlock_t *rw) {
    sem_post(&rw->writelock);
}

void readThread(void *arg) {
    printf("Create Reader\n");
    rwlock_acquire_readlock(arg);
    printf("Reader's is in... reading\n");
    usleep(1);
    rwlock_release_readlock(arg);
    printf("Finished reading\n");
}
void writeThread(void *arg) {
    printf("Create Writer\n");
    rwlock_acquire_writelock(arg);
    printf("Writer's is in... writing\n");
    usleep(1);
    rwlock_release_writelock(arg);
    printf("Finished writing\n");
}
