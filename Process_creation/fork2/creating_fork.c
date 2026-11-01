#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{

    pid_t pid;
    pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
    }
    else if (pid == 0)
    {
        printf("child pid  id %d\n", getpid());
    }
    else
    {
        printf("parent pid : %d And child pid : %d\n", getpid(), pid);
    }
    return 0;
}
