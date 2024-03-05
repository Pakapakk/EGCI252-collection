/*
Leader - group representative
- 6481328 Pakapak Jungjaroen
Worker
- 6481145 Yanaput Makbonsonglop
- 6481331 Andaman Jamprasitsakul
Presenter
- 6481322 Mark Kittiphat Kuprasertwong
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MEM_SIZE 4096
#define BUFSIZE 1024

struct mySHM {
  int written1;
  int written2;
  char data1[BUFSIZE];
  char data2[BUFSIZE];
  // char data[BUFSIZ];
};

int shmID;

void endChatHandler(int signo) {
  if (signo == SIGTERM) {
    shmctl(shmID, IPC_RMID, 0);
    exit(EXIT_SUCCESS);
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) { // if argc < 2 end program
    fprintf(stderr, "Usage: %s <[1, 2]>\n", *argv);
    exit(EXIT_FAILURE);
  }

  void *sh_mem = NULL;
  struct mySHM *sh_area;

  signal(SIGTERM, endChatHandler);  // set signal handler for SIGTERM

  char buffer[MEM_SIZE];

  shmID = shmget((key_t) 6481328, MEM_SIZE, 0666 | IPC_CREAT);  // Leader's ID to be shmID
  if (shmID == -1) {
    fprintf(stderr, "shmget failed\n");
    exit(EXIT_FAILURE);
  }

  sh_mem = shmat(shmID, NULL, 0);  // attach to shmID
  if (sh_mem == (void *)-1) {
    fprintf(stderr, "shmat failed\n");
    exit(EXIT_FAILURE);
  }

  sh_area = (struct mySHM *)sh_mem;  // point share area to attached shared mem

  if (!strcmp(argv[1], "1")) {
    int pid = fork();
    switch (pid) {
    case -1:
      perror("Forking failed\n");
      exit(EXIT_FAILURE);
    case 0: // child 1 receiving msg 2
      while (strncmp(sh_area->data2, "end chat", 8)) {
        if (sh_area->written2) {  // read msg from parent 2
          printf("%s", sh_area->data2);
          sh_area->written2 = 0;  // write enable
        }
        sleep(1);
      }
      kill(getppid(), SIGTERM);  // terminate parent
      raise(SIGTERM);  // terminate child itself
      break;
    default: // parent 1 sending msg 1
      while (strncmp(sh_area->data1, "end chat", 8)) {
        if (!sh_area->written1) {
          memset(buffer, '\0', MEM_SIZE);
          fgets(buffer, MEM_SIZE, stdin);
          memcpy(sh_area->data1, buffer, strlen(buffer) + 1); // Copy data into shared memory
          // fwrite(sh_area->data1, MEM_SIZE, 1, stdout);
          sh_area->written1 = 1;  // flag that it is sent by parent 2
          //printf("1 sent: %s\n", sh_area->data1);
        }
        sleep(1);
      }
      kill(pid, SIGTERM);  // terminate child
      raise(SIGTERM);  // terminate parent itself
      break;
    }
  }

  if (!strcmp(argv[1], "2")) {
    int pid = fork();
    switch (pid) {
    case -1:
      perror("Forking failed\n");
      exit(EXIT_FAILURE);
    case 0: // child 2 receiving msg 1
      while (strncmp(sh_area->data1, "end chat", 8)) {
        if (sh_area->written1) {  // read msg from parent 2
          printf("%s", sh_area->data1);
          sh_area->written1 = 0;  // write enable
        }
        sleep(1);
      }
      kill(getppid(), SIGTERM);  // terminate parent
      raise(SIGTERM);  // terminate child itself
      break;
    default: // parent 2 sending msg 2
      while (strncmp(sh_area->data2, "end chat", 8)) {
        if (!sh_area->written2) {
          memset(buffer, '\0', MEM_SIZE);
          fgets(buffer, MEM_SIZE, stdin);
          memcpy(sh_area->data2, buffer, strlen(buffer) + 1); // Copy data into shared memory
          // fwrite(sh_area->data2, MEM_SIZE, 1, stdout);
          sh_area->written2 = 1;  // flag that it is sent by parent 2
          //printf("1 sent: %s\n", sh_area->data1);
        }
        sleep(1);
      }
      kill(pid, SIGTERM);  // terminate child
      raise(SIGTERM);  // terminate parent itself
      break;
    }
  }
  exit(EXIT_SUCCESS);
}