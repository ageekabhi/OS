#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t sem;  //unnamed semaphore

void* task(void* arg){
    int id = *(int *)arg;

    sem_wait(&sem); //wait or Lock 
    printf("Thread %d entered critical secion. \n",id);

    sleep(1);
    printf("Thread %d leaving critical section.\n",id);

    sem_post(&sem);
    return NULL;

}

int main(){

    pthread_t t1 , t2;

    int a=1,b=2;
    
    //initializing unnamed semaphores 

    sem_init(&sem,0,1);
    //0 = between threads , 1 = initial value

    
    pthread_create(&t1,NULL,task,&a);
    pthread_create(&t2,NULL,task,&b);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    sem_destroy(&sem);
    return 0;
    

}
