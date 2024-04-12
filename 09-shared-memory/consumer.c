// consumer.c -> receive data from shared mem
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define MEM_SIZE 4096

struct shm_st {
  int written;
  char data[BUFSIZ];
};

int main(){
  int running = 1, shmID;
  void *sh_mem = NULL;
  struct shm_st *sh_area;
  key_t key;

  // Generate a unique key
  // key = ftok("/tmp", 'P');
  // if (key == -1) {
  //     perror("ftok");
  //     exit(EXIT_FAILURE);
  // }
  
  srand((unsigned int) getpid());  // generate random seed using process ID
  
  // shmID = shmget(key, MEM_SIZE, 0666 | IPC_CREAT);  // get shmID with size and perm or with IPC_CREAT (this line is for ftok)
  shmID = shmget((key_t) 1234, MEM_SIZE, 0666 | IPC_CREAT);  // get shmID with size and perm or with IPC_CREAT

  if(shmID == -1) fprintf(stderr, "shmget failed\n");

  if (shmID == -1) {
    exit(EXIT_FAILURE);
  }

  sh_mem = shmat(shmID, NULL, 0); // attach
  if (sh_mem == (void *) -1) {
    fprintf(stderr, "shmat failed\n");
    exit(EXIT_FAILURE);
  }

  printf("Memory attached at %X\n", sh_mem);
  sh_area = (struct shm_st *)sh_mem;  // type casting
  sh_area->written = 0;

  while (running) {
    if (sh_area->written) {
      printf("Data written in shared memory : %s\n", sh_area->data);
      sh_area->written = 0;
      if (strncmp(sh_area->data, "end", 3) == 0)
        running = 0;
    }
    sleep(rand() % 4);
  }
  if (shmdt(sh_mem) == -1 || shmctl(shmID, IPC_RMID, 0) == -1) {  // detach and remove ID from ipcs
    fprintf(stderr, "shmdt or shmctl failed\n");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}