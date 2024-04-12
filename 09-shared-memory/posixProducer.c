// Producer.c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// posix used dir name
#define SHM_NAME "/pshm"
#define MEM_SIZE 60

// 64 bytes in total
struct shm_st {
  int written;  // 4 bytes
  char data[MEM_SIZE];  // 60 bytes
};

int main() {
  int running = 1, shmfd, st_size;
  void *sh_mem = NULL;
  struct shm_st *sh_area;

  char buffer[BUFSIZ];
  st_size = sizeof(struct shm_st); // get size of struct
  shmfd = shm_open("/pshm", O_CREAT | O_RDWR, 0660);  // open file for shm
  if (shmfd == -1) {
    perror("shm_open failed");
    exit(EXIT_FAILURE);
  }
  ftruncate(shmfd, st_size);  // resize file to the size of struct
  sh_mem = mmap(0, st_size, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);  // map the share mem
  printf("Memory attached at %p\n", sh_mem);
  sh_area = (struct shm_st *)sh_mem;  // type casting
  sh_area->written = 0;

  while (running) {
    while (sh_area->written) {
      usleep(200);
    }
    printf("Enter data : ");
    fgets(buffer, BUFSIZ, stdin);
    strcpy(sh_area->data, buffer);
    sh_area->written = 1;
    if (strncmp(buffer, "end", 3) == 0)
      running = 0;
  }
  munmap(sh_mem, st_size);  // munmap with the size of struct
  close(shmfd);  // close
  exit(EXIT_SUCCESS);
}