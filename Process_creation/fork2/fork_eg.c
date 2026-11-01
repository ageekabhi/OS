#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void forkexample()
{
    pid_t p;
    p = fork();
    if (p < 0)
    {
        perror("Fork fail");
        exit(1);
    }
    else if (p == 0)
        printf("Hello from child!\n");

    else
        printf("Hello from Parent!\n");
}

int main()
    {
        forkexample();
        return 0;
    }