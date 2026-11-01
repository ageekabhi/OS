#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t lock;

void *test(void *arg)
{
    pthread_mutex_lock(&lock);
    printf("First lock done ");

    pthread_mutex_lock(&lock); // cause deadlock

    printf("Second lock done ");

    pthread_mutex_unlock(&lock);
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(){
    pthread_t t1;
    pthread_mutex_init(&lock,NULL);

    pthread_create(&t1,NULL,test,NULL);
    pthread_join(t1,NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}