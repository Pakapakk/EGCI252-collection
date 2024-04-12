// Read an Integer from a Memory-Mapped File, and Double It
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

// 0x100 = 256
#define FILE_LENGTH 0x100

int main(int argc, char *const argv[]) {
  int fd;
  void *file_memory;
  int integer;
  /* Open the file. */
  fd = open("demo", O_RDWR, S_IRUSR | S_IWUSR);
  /* Create the memory mapping. */
  file_memory = mmap(0, FILE_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  close(fd);

  // for(int i = 0; i < FILE_LENGTH;  i++){
  //   sscanf(file_memory + i, "%d", &integer);
  //   printf("%d", integer);
  // }

  /* Read the integer, print it out, and double it. */
  sscanf(file_memory, "%d", &integer); // scan the value in the file mem and store it in integer
  printf("value : %d\n", integer);
  sprintf((char *)file_memory, "%d\n", 2 * integer);  // reprint the value * 2 to the mmap

  /* Release the memory (unnecessary because the program exits). */
  munmap(file_memory, FILE_LENGTH);  // unmap with the size of file
  return 0;
}