#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 3

pthread_barrier_t barrier;

void* worker(void* arg)
{
    int id = *(int*)arg;
    printf("Thread %d: started its work...\n", id);
    sleep(id); // simulate different work times

    printf("Thread %d: reached the barrier.\n", id);
    pthread_barrier_wait(&barrier);  // wait for others

    printf("Thread %d: passed the barrier and continues!\n", id);
    return NULL;
}

int main()
{
    pthread_t threads[THREAD_COUNT];
    int ids[THREAD_COUNT];

    // Initialize barrier for THREAD_COUNT threads
    pthread_barrier_init(&barrier, NULL, THREAD_COUNT);

    for (int i = 0; i < THREAD_COUNT; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, worker, &ids[i]);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_barrier_destroy(&barrier);
    return 0;
}
