#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>

int counter = 0;
pthread_mutex_t lock;

void *inc(void *arg)
{
    for (int i = 0; i < 100; i++)
    {
        pthread_mutex_lock(&lock);
        counter++;
        printf("thread 1 counter : %d\n", counter);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

void *dec(void *arg)
{
    for (int i = 0; i < 100; i--)
    {
        pthread_mutex_lock(&lock);
        counter--;
        printf("thread 2 counter : %d\n", counter);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
   
}

int main()
{
    pthread_t t1,t2;
    pthread_mutex_init(&lock,NULL);

    pthread_create(&t1,NULL,inc,NULL);
    pthread_create(&t2,NULL,dec,NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);       // destroy mutex

    printf("\nFinal Counter Value: %d\n", counter);
    return 0;



}