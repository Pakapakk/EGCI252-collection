#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>  // for variable types
#include <fcntl.h> // open file

int main(void){
  char c;
  int in, out;

  in = open("file.in", O_RDONLY);
  out = open("file.out", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  while(read(in, &c, 1) == 1) write(out, &c, 1);

  return 0;
}