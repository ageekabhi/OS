#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int data = 0;
int available = 0; // condition flag

void* producer(void* arg)
{
    for (int i = 1; i <= 5; i++) {
        sleep(1); // Simulate data creation

        pthread_mutex_lock(&lock);
        data = i;          // Produce data
        available = 1;     // Mark data as available
        printf("Producer: produced data = %d\n", data);

        pthread_cond_signal(&cond); // Signal the consumer
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void* consumer(void* arg)
{
    for (int i = 1; i <= 5; i++) {
        pthread_mutex_lock(&lock);

        // Wait while data is not available
        while (available == 0) {
            printf("Consumer: waiting for data...\n");
            pthread_cond_wait(&cond, &lock);
        }

        // When signaled and available == 1
        printf("Consumer: consumed data = %d\n", data);
        available = 0; // Reset flag

        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main()
{
    pthread_t prod, cons;
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    return 0;
}
