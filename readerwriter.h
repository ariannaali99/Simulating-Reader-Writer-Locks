#ifndef READERWRITER_H
#define READERWRITER_H

#include <pthread.h>
#include <semaphore.h>

typedef struct _rwlock_t {
    sem_t orderMutex;
    sem_t lock;
    sem_t writelock;
    int readers;
} rwlock_t;

void rwlock_init(rwlock_t *rw);
void rwlock_acquire_readlock(rwlock_t *rw);
void rwlock_release_readlock(rwlock_t *rw);
void rwlock_acquire_writelock(rwlock_t *rw);
void rwlock_release_writelock(rwlock_t *rw);
void readThread(void *arg);
void writeThread(void *arg);

#endif