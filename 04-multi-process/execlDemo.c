#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t pid;
    pid = fork();
    printf("Process ID : %d\n", (int)pid);

    if(pid){
        execl("./print", "print", "2", "20", NULL);
    } else{
        execl("./print", "print", "1", "10", NULL);
    }
}