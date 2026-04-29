#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

/* ---------- semaphore simulation ---------- */
int mutex = 1;
int full  = 0;
int empty = BUFFER_SIZE;

void wait(int *s)   { --(*s); }
void signal(int *s) { ++(*s); }

/* ---------- shared buffer ---------- */
int buffer[BUFFER_SIZE];
int x = 0;   /* number of items currently in buffer */

/* ---------- producer ---------- */
void producer() {
    if (empty == 0) {
        printf("Buffer is full!\n");
        return;
    }
    wait(&mutex);
    wait(&empty);

    x++;
    buffer[x] = x;
    printf("Producer has produced: Item %d\n", x);

    signal(&full);
    signal(&mutex);
}

/* ---------- consumer ---------- */
void consumer() {
    if (full == 0) {
        printf("Buffer is empty!\n");
        return;
    }
    wait(&full);
    wait(&mutex);

    printf("Consumer has consumed: Item %d\n", x);
    x--;

    signal(&empty);
    signal(&mutex);
}

/* ---------- main ---------- */
int main() {
    int choice;

    do {
        printf("\nEnter 1.Producer 2.Consumer 3.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: producer(); break;
            case 2: consumer(); break;
            case 3: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 3);

    return 0;
}
