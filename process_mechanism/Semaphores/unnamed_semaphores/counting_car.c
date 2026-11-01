#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SPOTS 3

sem_t parking;        // counting semaphore
pthread_mutex_t lock; // mutex to protect spot array
int spots[SPOTS] = {0}; // 0 = free, 1 = occupied

int get_free_spot() {
    for (int i = 0; i < SPOTS; i++) {
        if (spots[i] == 0) {
            spots[i] = 1;
            return i; // return spot number
        }
    }
    return -1; // no free spot
}

void free_spot(int spot) {
    spots[spot] = 0;
}

void* car(void* arg) {
    int id = *(int*)arg;
    printf("Car %d arriving.\n", id);

    sem_wait(&parking); // wait for a free spot

    pthread_mutex_lock(&lock);
    int spot = get_free_spot(); // assign a specific spot
    pthread_mutex_unlock(&lock);

    printf("Car %d parked at spot %d\n", id, spot + 1);
    sleep(2); // parked
    printf("Car %d leaving spot %d\n", id, spot + 1);

    pthread_mutex_lock(&lock);
    free_spot(spot); // free the spot
    pthread_mutex_unlock(&lock);

    sem_post(&parking); // signal spot is free
    return NULL;
}

int main() {
    pthread_t cars[6];
    int ids[6];

    sem_init(&parking, 0, SPOTS);
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 6; i++) {
        ids[i] = i + 1;
        pthread_create(&cars[i], NULL, car, &ids[i]);
        sleep(1);
    }

    for (int i = 0; i < 6; i++)
        pthread_join(cars[i], NULL);

    sem_destroy(&parking);
    pthread_mutex_destroy(&lock);

    return 0;
}
