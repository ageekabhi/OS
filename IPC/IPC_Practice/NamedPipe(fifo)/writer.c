#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("myfifo", O_WRONLY);
    char msg[] = "Hello from writer process!";
    write(fd, msg, sizeof(msg));
    close(fd);
    return 0;
}

