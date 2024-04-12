#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void){
  FILE *writeFP;
  char buffer[BUFSIZ + 1];

  sprintf(buffer, "Hello World");
  writeFP = popen("od -c", "w");

  if(writeFP){
    fwrite(buffer, sizeof(char), strlen(buffer), writeFP);  // write to buffer using writeFP stream
    pclose(writeFP);
    exit(EXIT_SUCCESS);
  }
  exit(EXIT_FAILURE);
}