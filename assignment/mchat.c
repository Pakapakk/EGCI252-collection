/*
Leader - group representative
- 6481328 Pakapak Jungjaroen
Worker
- 6481145 Yanaput Makbonsonglop
- 6481331 Andaman Jamprasitsakul
Presenter
- 6481322 Mark Kittiphat Kuprasertwong
*/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

// define file length
#define FILE_LENGTH 4000
#define BUFSIZE 2000

void* fileMemory;

// struct for keeping user 1 and 2 written flag and data
struct mmchatFlag{
  int flag1;
  char data1[BUFSIZE];
  int flag2;
  char data2[BUFSIZE];
};

// do end chat activity : unmap and remove chat_log
void endChatHandler(int signo){
  if(signo == SIGTERM){
    munmap(fileMemory, FILE_LENGTH);
    system("rm -f chat_log");
    exit(EXIT_SUCCESS);
  }
}

int main(int argc, char* argv[]){
  if(argc != 2){
    printf("need 2 args\n");
    exit(EXIT_FAILURE);
  }
  
  // system("rm -f chat_log");
  signal(SIGTERM, endChatHandler); // set handler for SIGTERM

  char buffer[BUFSIZE];

  // file init
  int fileDescriptor = open("chat_log", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  lseek (fileDescriptor, FILE_LENGTH + 1, SEEK_SET);
  write (fileDescriptor, "", 1);
  lseek (fileDescriptor, 0, SEEK_SET);

  // mmap init
  fileMemory = mmap (0, FILE_LENGTH, PROT_WRITE | PROT_READ, MAP_SHARED, fileDescriptor, 0);
  close (fileDescriptor);

  // cast struct pointer to mmap to make it point to struct
  struct mmchatFlag* fileArea = (struct mmchatFlag*)fileMemory;

  // user 1
  if(!strcmp(argv[1], "1")){
    int pid = fork();
    switch(pid){
      case -1 :
        printf("Fork failed\n");
        exit(EXIT_FAILURE);
        break;
      case 0 : // child -> receiving msg 2
        while (strncmp(fileArea->data2, "end chat", 8)) {
          if(fileArea->flag2 == 1){
            printf("%s", fileArea->data2);
            fileArea->flag2 = 0;
          }
        }

        kill(getppid(), SIGTERM);  // terminate parent
        break;
      default : // parent -> sending msg 1
        while(strncmp(fileArea->data1, "end chat", 8)){
          memset(buffer, '\0', BUFSIZE);
          fgets(buffer, 256, stdin);
          sprintf(fileArea->data1, "%s", buffer);
          fflush(stdin);
          fileArea->flag1 = 1;
        }

        kill(pid, SIGTERM);  // terminate child
        break;
    }
  }

  // user 2
  if(!strcmp(argv[1], "2")){
    int pid = fork();
    switch(pid){
      case -1 :
        printf("Fork failed\n");
        exit(EXIT_FAILURE);
        break;
      case 0 : // child -> receiving msg 1
        while(strncmp(fileArea->data1, "end chat", 8)){
          if(fileArea->flag1 == 1){
            printf("%s", fileArea->data1);
            fileArea->flag1 = 0;
          }
        }

        kill(getppid(), SIGTERM);  // terminate parent
        break;
      default : // parent -> sending msg 2
        while(strncmp(fileArea->data2, "end chat", 8)){
          memset(buffer, '\0', BUFSIZE);
          fgets(buffer, 256, stdin);
          sprintf(fileArea->data2, "%s", buffer);
          fflush(stdin);
          fileArea->flag2 = 1;
        }

        kill(pid, SIGTERM);  // terminate child
        break;
    }
  }
  exit(EXIT_FAILURE);  // exit
}