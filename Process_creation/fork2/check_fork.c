#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
    pid_t p = fork();

    if (p < 0)
    {
        printf("fork failed!\n");
        exit(1);
    }
    else if (p == 0)
    {
        printf("Child process PID: %d\n", getpid());
    }
    else
    {
        printf("Parent process PID: %d\n", getpid());
    }

    return 0;
}
