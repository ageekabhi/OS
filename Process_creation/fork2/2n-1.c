#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    fork();
    sleep(1);
    fork();
    sleep(1);
    fork();
    printf("Hello world\n");
    return 0;
}