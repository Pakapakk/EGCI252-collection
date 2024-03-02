/*
Leader - group representative
- 6481328 Pakapak Jungjaroen
Worker
- 6481145 Yanaput Makbonsonglop
- 6481331 Andaman Jamprasitsakul
Presenter
- 6481322 Mark Kittiphat Kuprasertwong
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void){
  char block[512];
  int in, out, nread;
  char null_char = '\0';
  int newlen = 0;
  
  in = open("file.in", O_RDONLY);
  out = open("file.out", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

  while((nread = read(in, block, sizeof(block))) > 0){
    write(out, block, nread);
    newlen += nread;
  }
  int startnull = (newlen / 2) - 8; // half of 16
  lseek(out, startnull, SEEK_SET);
  for(int i = 0; i < 16; i++){
    write(out, &null_char, 1);
  }
  return 0;
}