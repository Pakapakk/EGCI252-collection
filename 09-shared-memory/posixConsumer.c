// Consumer.c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// named share mem using "/something"
#define SHM_NAME "/pshm"
#define MEM_SIZE 60

// 64 bytes
struct shm_st {
  int written;   // 4 bytes
  char data[MEM_SIZE];  // 60 bytes
};

int main() {
  int running = 1, shmfd, st_size;
  void *sh_mem = NULL;
  struct shm_st *sh_area;

  st_size = sizeof(struct shm_st);  // get size of struct
  shmfd = shm_open("/pshm", O_CREAT | O_RDWR, 0660);  // open file for shm
  if (shmfd == -1) {
    perror("shm_open failed");
    exit(EXIT_FAILURE);
  }
  ftruncate(shmfd, st_size); // resize it to size of struct
  sh_mem = mmap(0, st_size, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0); // using mmap to map
  printf("Memory attached at %p\n", sh_mem);
  sh_area = (struct shm_st *)sh_mem;
  sh_area->written = 0;

  while (running) {
    if (sh_area->written) {
      printf("Data written in shared memory : %s", sh_area->data);
      sh_area->written = 0;
      if (strncmp(sh_area->data, "end", 3) == 0)
        running = 0;
    }
    usleep(200);
  }
  munmap(sh_mem, st_size);  // mmunmap with the size of struct (size of struct)
  close(shmfd);  // close 
  if (shm_unlink(SHM_NAME) == -1) {  // unlink
    perror("shm_unlink failed");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}