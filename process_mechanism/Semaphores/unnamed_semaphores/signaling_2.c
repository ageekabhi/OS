#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>

sem_t signal_sem;
pthread_mutex_t lock;
// pthread_mutex_t lock2;

void *sender(void *arg)
{
    // pthread_mutex_lock(&lock);
    printf("Sender : Preaparing Data..\n");
    sleep(1);
    printf("Sender : data ready ! Signaling receiver.\n");

    sem_post(&signal_sem);
    // pthread_mutex_unlock(&lock);
    return NULL;
}

void *receiver(void *arg)
{
    // pthread_mutex_lock(&lock);
    printf("Receiver : waiting  for data ..\n");
    sem_wait(&signal_sem);
    printf("Receiver : data received ..Processing \n");
    // pthread_mutex_unlock(&lock);
    return NULL;
}

int main()
{
    pthread_t t1, t2, t3, t4;

    sem_init(&signal_sem, 0, 0);

    pthread_create(&t1, NULL, receiver, NULL);
    pthread_create(&t2, NULL, sender, NULL);
    pthread_create(&t3, NULL, receiver, NULL);
    pthread_create(&t4, NULL, sender, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    sem_destroy(&signal_sem);
    return 0;
}