#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t lock;
void* test(void* arg){
    pthread_mutex_lock(&lock);
    printf("First Lock done\n");

    pthread_mutex_lock(&lock);
    printf("second lock done\n");

    pthread_mutex_unlock(&lock);
    printf("First Unlock done \n");

    pthread_mutex_unlock(&lock);
    printf("Second unlock done\n");

    return NULL;
}

int main(){
    pthread_t t;
    pthread_mutexattr_t attr;

    //set type = RECURSIVE
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&lock,&attr);

    pthread_mutexattr_destroy(&attr);

    pthread_create(&t, NULL,test,NULL);
    pthread_join(t,NULL);

    pthread_mutex_destroy(&lock);
    return 0;

}