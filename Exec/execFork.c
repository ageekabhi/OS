#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<wait.h>
int main(){
    pid_t pid = fork();

    if(pid == 0){
        execlp("ls","ls","-l",NULL);
        perror("exec failed");


        
        // execl
        // execle
        // execlp
        // execv
        // execve
        // execvp

    } 
    else
    {
        wait(NULL);
        printf("Child finished executing ");
    }
}