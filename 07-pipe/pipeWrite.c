#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void){
  int n_bytes;
  int pipeFD[2];
  int pid;
  char buffer[BUFSIZ + 1], data[] = "12345";

  memset(buffer, '\0', sizeof(buffer));

  if(pipe(pipeFD) == 0){
    pid = fork();
    switch(pid){
      case -1:
        fprintf(stderr, "Fork failed\n");
        exit(EXIT_FAILURE);
      case 0:  // read
        sprintf(buffer, "%d", pipeFD[0]);  // print content pipe[0] into buffer
        execl("./read", "read", buffer, (char *)0);  // (char *)0 -> pointer to NULL // use buffer as an argv[1]
        exit(EXIT_SUCCESS);
      default:  // write
        n_bytes = write(pipeFD[1], data, strlen(data));  // write data into pipeFD[1] (write pipe)
        printf("%d bytes have been written from %d !\n", n_bytes, getpid());
    }
  }

  wait(NULL);
  exit(EXIT_SUCCESS);
}