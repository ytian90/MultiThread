/*
	sem.c
	CSC716 Project
	Created By Yu Tian on 12/10/15
*/

#include <unistd.h>
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */
#include <semaphore.h>  /* Semaphore */
#include <unistd.h>
#include <time.h>
#define numReaders 9
#define numWriters 3

void reader(void *ptr);
void writer(void *ptr);
int getRand();

sem_t wrt, mutex;
time_t start_t, now_t;
int counter;
int acReaders = 0;
double diff_t, total_t = 20.0;

int main() {
    sem_init(&wrt, 0, 1);
    sem_init(&mutex, 0, 1);

    int r[numReaders];
    int w[numWriters];
    int i = 0;

    for (i = 0; i < numReaders; i++) {
        r[i] = i;
    }

    for (i = 0; i < numWriters; i++) {
        w[i] = i;
    }
/*
    for (i = 0; i < 10; i++) {
        int temp = getRand();
        printf("%d ", temp);
    }
*/
    pthread_t thread_r1;
    pthread_t thread_r2;
    pthread_t thread_r3;
    pthread_t thread_r4;
    pthread_t thread_r5;
    pthread_t thread_r6;
    pthread_t thread_r7;
    pthread_t thread_r8;
    pthread_t thread_r9;

    pthread_t thread_w1;
    pthread_t thread_w2;
    pthread_t thread_w3;

    time(&start_t);

    pthread_create(&thread_r1, NULL, (void*) &reader, (void*) &r[0]);
    pthread_create(&thread_r2, NULL, (void*) &reader, (void*) &r[1]);
    pthread_create(&thread_r3, NULL, (void*) &reader, (void*) &r[2]);
    pthread_create(&thread_r4, NULL, (void*) &reader, (void*) &r[3]);
    pthread_create(&thread_r5, NULL, (void*) &reader, (void*) &r[4]);
    pthread_create(&thread_r6, NULL, (void*) &reader, (void*) &r[5]);
    pthread_create(&thread_r7, NULL, (void*) &reader, (void*) &r[6]);
    pthread_create(&thread_r8, NULL, (void*) &reader, (void*) &r[7]);
    pthread_create(&thread_r9, NULL, (void*) &reader, (void*) &r[8]);

    pthread_create(&thread_w1, NULL, (void*) &writer, (void*) &w[0]);
    pthread_create(&thread_w2, NULL, (void*) &writer, (void*) &w[1]);
    pthread_create(&thread_w3, NULL, (void*) &writer, (void*) &w[2]);

    pthread_join(thread_r1, NULL);
    pthread_join(thread_r2, NULL);
    pthread_join(thread_r3, NULL);
    pthread_join(thread_r4, NULL);
    pthread_join(thread_r5, NULL);
    pthread_join(thread_r6, NULL);
    pthread_join(thread_r7, NULL);
    pthread_join(thread_r8, NULL);
    pthread_join(thread_r9, NULL);
    pthread_join(thread_w1, NULL);
    pthread_join(thread_w2, NULL);
    pthread_join(thread_w3, NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    exit(0);

}

int getRand() {
    int res;
    res = rand() % 5 + 1;
    return res;
}

void reader(void *ptr) {
    time(&now_t);
    while (difftime(now_t, start_t) < total_t) {
        int st_b = getRand();
        int st_i = getRand();
        int st_a = getRand();

        int x;
        x = *((int *) ptr);
        printf("Reader Thread %d: Waiting to enter critical region...\n", x);
        sleep(st_b);

        sem_wait(&mutex);
        acReaders++;
        if (acReaders == 1) sem_wait(&wrt);
        sem_post(&mutex);
        // start critical region

        printf("Reader Thread %d in critical region...\n", x);
        printf("active readers: %d\n", acReaders);
        printf("Now Reader Thread sleep %d seconds\n", st_i);
        sleep(st_i);
        printf("Reader Thread %d is reading files...\n", x);
        printf("Reader Thread %d exiting critical region...\n", x);
    /*
        printf("Reader Thread %d: Now in critical region...\n", x);

    //    printf("Number of readers : %d\n", numreaders);

        printf("Reader Thread %d: Counter Value: %d\n", x, counter);
        printf("Reader Thread %d: Incrementing Counter...\n", x);
        counter++;
        printf("Reader Thread %d: New Counter Value: %d\n", x, counter);
        printf("Active Readers: %d\n", acReaders);
        printf("Reader Thread %d: Exiting critical region...\n", x);
    */
        // end critical region
        sem_wait(&mutex);
        acReaders--;
        if (acReaders == 0) sem_post(&wrt);
        sem_post(&mutex);
        sleep(st_a);
    }

}

void writer(void *ptr) {
    time(&now_t);
    while (difftime(now_t, start_t) < total_t) {
        int st_b = getRand();
        int st_i = getRand();
        int st_a = getRand();

        int x;
        x = *((int *) ptr);
        printf("Writer Thread %d: Waiting to enter critical region...\n", x);
        sleep(st_b);

        sem_wait(&wrt);
        // start critical region

        printf("Writer Thread %d in critical region...\n", x);
        printf("Writer Thread %d is writing files...\n", x);
        printf("Now Writer Thread sleep %d seconds\n", st_i);
        sleep(st_i);
        printf("Writer Thread %d exiting critical region...\n", x);
    /*
        printf("Writer Thread %d: Now in critical region...\n", x);
        printf("Writer Thread %d: Counter Value: %d\n", x, counter);
        printf("Writer Thread %d: Incrementing Counter...\n", x);
        counter++;
        printf("Writer Thread %d: New Counter Value: %d\n", x, counter);
        printf("Wrtier Thread %d: Exiting critical region...\n", x);
    */
        // end critical region
        sem_post(&wrt);
        sleep(st_a);
    }
}

