#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main(){
    int fd[2];
    pid_t pid;

    char msg[]="hello im abhi";
    char buf[50];

    pipe(fd);
    pid =fork();

    if(pid == 0){
        close(fd[1]);
        read(fd[0],buf,sizeof(buf));

        printf("child received : %s\n",buf);
        close(fd[0]);
        printf("Parent id : %d and child id %d\n",getppid(),getpid());

    }else{

        close(fd[0]);
        write(fd[1],msg,strlen(msg)+1);
        close(fd[1]);
        printf("Parrent id : %d and child id %d\n",getppid(),getpid());

    }

    return 0;

}