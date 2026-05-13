#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS   8    /* how many items the producer makes (A, B, C, ...) */

/* ---------- shared buffer ---------- */
char buffer[BUFFER_SIZE];
int  in  = 0;   /* next write slot */
int  out = 0;   /* next read  slot */

/* ---------- synchronisation primitives ---------- */
pthread_mutex_t mutex;
sem_t           empty;   /* free  slots (init = BUFFER_SIZE) */
sem_t           full;    /* filled slots (init = 0)          */

/* ---------- producer thread ---------- */
void *producer(void *arg)
{
    for (int i = 0; i < NUM_ITEMS; i++) {
        char item = 'A' + i;       /* A, B, C, D, … */

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer produced %c\n", item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        usleep(100000);            /* 0.1 s between productions */
    }
    return NULL;
}

/* ---------- consumer thread ---------- */
void *consumer(void *arg)
{
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        char item = buffer[out];
        printf("Consumer consumed %c\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        usleep(300000);            /* 0.3 s – consumer is slower, so producer gets ahead */
    }
    return NULL;
}

/* ---------- main ---------- */
int main(void)
{
    pthread_t prod_tid, cons_tid;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full,  0, 0);

    pthread_create(&prod_tid, NULL, producer, NULL);
    pthread_create(&cons_tid, NULL, consumer, NULL);

    pthread_join(prod_tid, NULL);
    pthread_join(cons_tid, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
