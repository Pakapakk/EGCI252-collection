#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(void){
  char block[512];
  int in, out, n_read;

  in = open("file.in", O_RDONLY);
  out = open("file.out", O_WRONLY | O_CREAT, S_IRUSR|S_IWUSR);
  while((n_read = read(in, block, sizeof(block))) > 0){
    write(out, block, n_read);
  }
  
  return 0;
}