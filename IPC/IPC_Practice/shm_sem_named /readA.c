#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>

int main(){
int fd = shm_open("/myshm",O_RDWR,0666);
char *ptr = mmap(0,1024,PROT_READ,MAP_SHARED,fd,0);

sem_t *sem = sem_open("/mysem",0);

sem_wait(sem);

printf("Received : %s\n",ptr);

munmap(ptr,1024);
close(fd);
return 0;
}
