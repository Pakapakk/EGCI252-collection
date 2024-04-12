#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void rx_int(int sig)
{ 
  printf("SIGINT - %d Received!!!\n", sig); 
}

int main(void)
{
  struct sigaction act;

  act.sa_handler = rx_int;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  //act.sa_flags = SA_NOCLDSTOP;

  // sys V signal
  //signal(SIGINT, rx_int);
  //POSIX signal
  sigaction(SIGINT, &act, 0);

  if(fork() == 0){
    printf("Child Process\n");
    sleep(3);
  } else{
    while(1) {
      printf("Running...\n"); 
      sleep(1); 
    }
  }
}