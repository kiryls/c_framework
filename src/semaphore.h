#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "defines.h"
#include <sys/sem.h>
#include <sys/ipc.h>
#include <errno.h>
#include <assert.h>

#ifndef ARENA_H
    #include "arena.h"
    #define ARENA_H
#endif /* ARENA_H */

typedef struct {
    u32 sem_id;
    u32 initial_value;
} Semaphore;

Semaphore *semaphore_create(Arena *arena, u32 key, i32 initial_value);

void semaphore_wait(Semaphore* sem);

void semaphore_signal(Semaphore* sem);

void semaphore_destroy(Semaphore* sem);

// #ifdef SEMAPHORE_IMPLEMENTATION

Semaphore *semaphore_create(Arena *arena, u32 key, i32 initial_value) {

    assert(arena && "Arena is null");

    Semaphore *sem = (Semaphore*) arena_alloc(arena, sizeof(Semaphore));

    assert(sem && "Sem is null");

    sem->sem_id = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
    /*
    if (sem->sem_id == -1) {
        if (errno == EEXIST) {
            sem->sem_id = semget(key, 1, 0666);
            if (sem->sem_id == -1) {
                perror("Failed to get semaphore");
                return null;
            }
        } else {
            perror("Failed to create semaphore");
            return null;
        }
    }
    */

    assert(sem->sem_id > -1 && "Sem already existing or error during its creation");

    if(semctl(sem->sem_id, 0, SETVAL, initial_value) == -1) {
        perror("Failed to initialize the semaphore");
        return null;
    }

    return sem;
}

void semaphore_wait(Semaphore* sem) {
    struct sembuf op;

    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = 0;

    if(semop(sem->sem_id, &op, 1) == -1) {
        perror("Failed to wait on semaphore");
    }
}

void semaphore_signal(Semaphore* sem) {
    struct sembuf op;

    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = 0;

    if(semop(sem->sem_id, &op, 1) == -1) {
        perror("Failed to signal semaphore");
    }
}

void semaphore_destroy(Semaphore *sem) {
    if(semctl(sem->sem_id, 0, IPC_RMID) == -1) {
        perror("Failed to destroy semaphore");
    }
}

#endif /* SEMAPHORE_IMPLEMENTATION */

#endif /* SEMAPHORE_H */
