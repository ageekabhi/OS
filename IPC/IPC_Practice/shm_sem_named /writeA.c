#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>

int main(){

int fd = shm_open("/myshm",O_CREAT | O_RDWR,0666);
ftruncate(fd,1024);

char *ptr = mmap(0,1024,PROT_WRITE,MAP_SHARED,fd,0);
sem_t *sem = sem_open("/mysem",O_CREAT,0666,0);

sprintf(ptr,"hello from shared memory!!");

sem_post(sem);

munmap(ptr,1024);
close(fd);
}

