#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){
  int pipeFD[2];
  int n_bytes;
  int store;
  char buffer[BUFSIZ + 1];

  memset(buffer, '\0', sizeof(buffer));

  sscanf(argv[1], "%d", &store);  // read from writer buffer (argv[1]) and store it in store
  n_bytes = read(store, buffer, BUFSIZ);  // read to count bytes of data from store and keep it in buffer
  printf("%d bytes have been read from %d : %s\n", n_bytes, getpid(), buffer); // print
  exit(EXIT_SUCCESS);
}