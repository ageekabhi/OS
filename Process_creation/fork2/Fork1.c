#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t p = fork();
    // if(p<0){
    //     printf("fork fail\n");
    //     // exit(1);
    // }
    // else
    // printf("Hello world!,proces_id(PID) = %d\n",getpid());

    if (p == 0)
        printf("Child process PID: %d\n", getpid());
    else
        printf("Parent process PID: %d\n", getpid());

    return 0;
}
