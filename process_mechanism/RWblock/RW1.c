#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_rwlock_t rwlock;
int shared_data = 0;

void *reader(void *arg)
{
    int id = *(int *)arg;

    pthread_rwlock_rdlock(&rwlock);
    printf("Reader %d : read shared_data = %d\n", id, shared_data);
    sleep(1);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

void *writer(void *arg)
{
    int id = *(int *)arg;
    pthread_rwlock_wrlock(&rwlock);
    shared_data++;
    printf("Writer %d: updated shared data to %d\n", id, shared_data);
    sleep(1);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

int main()
{
    pthread_t r1, r2, w1, r3;
    int id1 = 1, id2 = 2, id3 = 3, id4 = 4;

    pthread_rwlock_init(&rwlock, NULL);

    pthread_create(&r1, NULL, reader, &id1);
    pthread_create(&r2, NULL, reader, &id1);
    pthread_create(&w1, NULL, writer, &id3);
    pthread_create(&r3, NULL, reader, &id1);
    
    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);
    pthread_join(r3, NULL);

    pthread_rwlock_destroy(&rwlock);
    return 0;
}