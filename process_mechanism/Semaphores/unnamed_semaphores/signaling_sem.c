#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>

sem_t signal_sem;

void *sender(void *arg)
{
    printf("Sender : Preaparing Data..\n");
    sleep(1);
    printf("Sender : data ready ! Signaling receiver.\n");

    sem_post(&signal_sem);
    return NULL;
}

void* receiver(void* arg){
    printf("Receiver : waiting  for data ..\n");
    sem_wait(&signal_sem);
    printf("Receiver : data received ..Processing \n");
    return NULL;


}

int main(){
    pthread_t t1,t2;

    sem_init(&signal_sem,0,0);

    pthread_create(&t1,NULL,receiver,NULL);
    pthread_create(&t2,NULL,sender,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    sem_destroy(&signal_sem);
    return 0;

}