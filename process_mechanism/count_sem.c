#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define THREAD_COUNT 5
#define MAX_ALLOWED  2  

sem_t count_sem; 

void* worker(void* arg) {
    int id = *(int*)arg;

    printf("Thread %d: waiting for resource...\n", id);
    sem_wait(&count_sem); 

    // ----- Critical section -----
    printf("Thread %d: entered critical section.\n", id);
    sleep(2);  
    printf("Thread %d: leaving critical section.\n", id);
    // ----------------------------

    sem_post(&count_sem); 

    return NULL;
}

int main() {
    pthread_t threads[THREAD_COUNT];
    int thread_ids[THREAD_COUNT];

    sem_init(&count_sem, 0, MAX_ALLOWED);

  
    for (int i = 0; i < THREAD_COUNT; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, worker, &thread_ids[i]);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&count_sem);
    printf("All threads finished.\n");
    return 0;
}
