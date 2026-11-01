#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem;

void *taskA(void *arg)
{
    printf("Task A :--> preparing\n");
    sleep(1);
    printf("Task A :--> signaling Task B...\n");
    sem_post(&sem); // signal B to start
    return NULL;
}

void *taskB(void *arg)
{
    printf("Task B : waiting for signal from A ...\n");
    sleep(1);
    printf("Task B : received signal...processing \n");
    sem_wait(&sem);
    return NULL;
}

int main()
{
    pthread_t a, b;
    sem_init(&sem, 0, 0); // initialixe with 0 (both)

    pthread_create(&a, NULL, taskA, NULL);
    pthread_create(&b, NULL, taskB, NULL);

    pthread_join(a, NULL);
    pthread_join(b, NULL);
    sem_destroy(&sem);
}