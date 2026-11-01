#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#define _GNU_SOURCE  
#include <unistd.h> 

pthread_mutex_t rlock;

void recursiveFun(int count){
    if(count == 0)
    return;

    pthread_mutex_lock(&rlock);
    printf("Locked %d\n",count);

    recursiveFun(count -1);

    pthread_mutex_unlock(&rlock);
    printf("Unlocked %d\n",count);

}

int main(){
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
        #ifdef PTHREAD_MUTEX_RECURSIVE_NP
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
    #else
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    #endif
    // pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&rlock,&attr);

    recursiveFun(3);

    pthread_mutex_destroy(&rlock);
    return 0;
}