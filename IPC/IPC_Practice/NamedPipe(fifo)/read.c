#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int fd = open("myfifo",O_RDONLY);
	char buff[100];
	read(fd,buff,sizeof(buff));
	printf("Reader got: %s\n",buff);
	close(fd);
	return 0;
}


