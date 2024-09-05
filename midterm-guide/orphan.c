#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>

int main(){
  int pid = fork();

  if(pid){
    // sleep(3);
    printf("This is Parent\n");
  } else{
    // sleep(6);
    while(1){
      printf("This is Child\n");
      sleep(1);
    }
  }
  return 0;
}