/*
	ex1.c
	CSC716 Project
	Created By Yu Tian on 12/10/15
*/
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NITER 1000000

int cnt = 0;
sem_t mutex;

void * Count (void *a) {
    sem_wait(&mutex);
    int i, tmp;
    for (i = 0; i < NITER; i++) {
        tmp = cnt;
        tmp++;
        cnt = tmp;
    }
    sem_post(&mutex);
}

int main(int argc, char * argv[]) {
    sem_init(&mutex, 0, 1);

    pthread_t tid1, tid2;
    if (pthread_create(&tid1, NULL, Count, NULL)) {
        printf("\n Error creating thread 1");
        exit(1);
    }

    if (pthread_create(&tid2, NULL, Count, NULL)) {
        printf("\n Error creating thread 2");
        exit(1);
    }

    if (pthread_join(tid1, NULL)) {
        printf("\n Error joining thread");
        exit(1);
    }

    if (pthread_join(tid2, NULL)) {
        printf("\n Error joining thread");
        exit(1);
    }

    if (cnt < 2 * NITER) {
        printf("\n Boom! cnt is [%d], should be %d\n", cnt, 2 * NITER);
    } else {
        printf("\n Ok! cnt is [%d]\n", cnt);
    }

    pthread_exit(NULL);
}

