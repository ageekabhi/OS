#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define PARKING_SPOT 3

sem_t sem;

void *car(void *arg)
{
    int car_id = *(int *)arg;

    printf("car %d wainting for parking spot ...\n", car_id);
    sem_wait(&sem);

    printf("car %d parked.\n", car_id);
    // sleep(1);

    printf("car %d leaving.\n", car_id);
    sem_post(&sem);

    return NULL;
}

int main()
{
    pthread_t cars[6];
    int car_ids[6];

    sem_init(&sem, 0, PARKING_SPOT);

    for (int i = 0; i < 6; i++)
    {
        car_ids[i] = i + 1;

        pthread_create(&cars[i], NULL, car, &car_ids[i]);
        // sleep(1);
    }
    for (int i = 0; i < 6; i++)
    {
        pthread_join(cars[i], NULL);

        sem_destroy(&sem);
        return 0;
        // pthread_create(&cars[i],NULL,car,&car_ids[i]);
        // sleep(1);
    }
}