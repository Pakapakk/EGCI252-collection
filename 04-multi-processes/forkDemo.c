#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid;
    char *msg;
    int n;
    printf("Starting fork program.\n");
    pid = fork();

    switch(pid){
        case -1 : _exit(1);
        case 0 : msg = "Child!\n"; n = 10; break;
        default : msg = "Parent!\n"; n = 5; break;
    }
    for(; n > 0; n--){
        printf("%s: %d\n", msg, n);
        sleep(1);
    }
    if(pid){
        int statVal;
        pid_t childPID;
        childPID = wait(&statVal);
        printf("Child has finished : PID = %d\n", childPID);
        if(WIFEXITED(statVal)){
            printf("Child excited with code %d\n", WIFEXITED(statVal));
        }else{
            printf("Child terminated abnormally\n");
        }
    }
    _exit(0);
}