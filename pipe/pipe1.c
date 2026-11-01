#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];                  // fd[0] = read end, fd[1] = write end
    pid_t pid;
    char write_msg[] = "Hello Parent! Message from Child.\n";
    char read_msg[100];

    // Create the pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Fork a child process
    pid = fork();
    
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        close(fd[0]);          // Close read end, child only writes

        write(fd[1], write_msg, strlen(write_msg) + 1);  
        close(fd[1]);          // Close write end after writing

        exit(0);
    }
    else {
        close(fd[1]);          // Close write end, parent only reads

        read(fd[0], read_msg, sizeof(read_msg));
        printf("Parent received: %s", read_msg);

        close(fd[0]);          // Close read end
    }

    return 0;
}
