// Write a Random Number to a Memory-Mapped File
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

// 0x100 = 256
#define FILE_LENGTH 0x100

int randDev;

/* Return a uniformly random number in the range [low,high]. */
int random_range(unsigned const low, unsigned const high) {
  unsigned const range = high - low + 1;
  return low + (int)(((double)range) * rand() / (RAND_MAX + 1.0));
}

// /* Return a uniformly random number in the range [low,high]. */
// int random_range(unsigned const low, unsigned const high) {
//   unsigned int number;
//   unsigned const range = high - low + 1;
//   read(randDev, &number, sizeof(number));
//   return low + (int)(((double)range) * number / (UINT_MAX + 1.0));
// }

int main(int argc, char *const argv[]) {
  int fileDescriptor;
  void *file_memory;

  srand(time(NULL));
  randDev =  open("/dev/urandom", O_RDONLY);

  // file init
  /* Prepare a file large enough to hold an unsigned integer. */
  fileDescriptor = open("demo", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  lseek(fileDescriptor, FILE_LENGTH + 1, SEEK_SET);
  write(fileDescriptor, "", 1); // write the file to change the size
  lseek(fileDescriptor, 0, SEEK_SET);  // go back to the beginning

  /* Create the memory mapping. */
  // 1st 0 = NULL -> system handle the location of the file in the heap
  // last 0 = offset -> map start from the beginning of the file
  file_memory = mmap(0, FILE_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fileDescriptor, 0);
  close(fileDescriptor);

  /* Write a random integer to memory-mapped area. */
  sprintf((char *)file_memory, "%d\n", random_range(-100, 100));

  /* Release the memory (unnecessary because the program exits). */
  munmap(file_memory, FILE_LENGTH);

  return 0;
}