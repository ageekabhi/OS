#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CONSUMER 3

sem_t data_ready;

void *producer(void *arg)
{

    printf("Producer : Generating data ..\n");
    sleep(1);
    printf("Producer : data ready, signaling consumer..\n");
    for (int i = 0; i < CONSUMER; i++)
    {
        sem_post(&data_ready);
    }
    return NULL;
}

void *consumer(void *arg)
{
    int id = *(int *)arg;
    printf("consumer %d : waiting for data ...\n", id);
    sem_wait(&data_ready);
    printf("Consumer %d: Got  data! Processing...\n ", id);
    return NULL;
}

int main()
{
    pthread_t prod, cons[CONSUMER];

    int ids[CONSUMER] = {1, 2, 3};

    sem_init(&data_ready, 0, 0);

    pthread_create(&prod, NULL, producer, NULL);
    for (int i; i < CONSUMER; i++)
        pthread_create(&cons[i], NULL, consumer, &ids[i]);

    pthread_join(prod, NULL);
    for (int i = 0; i < CONSUMER; i++)
        pthread_join(cons[i], NULL);

    sem_destroy(&data_ready);
    return 0;
}