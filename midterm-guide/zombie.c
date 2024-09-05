#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

int main() {
    pid_t child_pid;
    child_pid = fork();

    if (child_pid > 0) { // parent
        while(1);
        //wait(NULL);
        printf("Parent process exiting...\n");
    } else if (child_pid == 0) { // child
        // child finish first + parent not get exit code => zom
        printf("Child process exiting...\n");
        exit(0);
    } else { 
        fprintf(stderr, "Fork failed!\n");
        return 1;
    }

    return 0;
}