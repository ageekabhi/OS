#include<stdio.h>
#include<unistd.h>
#include<sys/mman.h>
#include<semaphore.h>
#include<fcntl.h>
#include<string.h>

int main(){
	int fd = shm_open("/myshm",O_CREAT | O_RDWR,0666);
	ftruncate(fd,1024);

	char *ptr = mmap(NULL,1024,PROT_WRITE,MAP_SHARED,fd,0);

	sem_t *sem = sem_open("/mysem",O_CREAT,0666,1);

	sem_wait(sem);
	sprintf(ptr,"hello from shared memory writer !");
	sem_post(sem);

	munmap(ptr,1024);
	close(fd);
	return 0;
}


