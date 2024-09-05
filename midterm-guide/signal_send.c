#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(){
  int pid;
  pid = fork();

  if(pid == 0){ // child
    while(1){
      printf("child running\n");
      sleep(1);
    }
  } else if(pid){
    int t;

    kill(pid, SIGSTOP);
    do{
      printf("Time input : ");
      scanf("%d", &t);

      if(t > 0){
        kill(pid, SIGCONT);
        sleep(t);
        kill(pid, SIGSTOP);
      }
    }while(t > 0);

    kill(pid, SIGKILL);
  }

  return 0;
}