#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cond = PTHREAD_COND_INITIALIZER;

int ready =0;

void* waiter(void* arg)
{
    pthread_mutex_lock(&lock);
    while(ready==0){
        printf("waiter : waiting for condition...\n");
        pthread_cond_wait(&cond, &lock);

    }
    printf("Waiter : condition met ! Proceeding..\n");
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* signaler(void* arg){
    sleep(1);
    pthread_mutex_lock(&lock);
    ready=1;
    printf("Signaler : Condition set ..Signaling waiter...\n");
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
    return NULL;

}
int main(){

    pthread_t t1,t2;
    pthread_create(&t1,NULL,waiter,NULL);
    pthread_create(&t2,NULL,signaler,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}