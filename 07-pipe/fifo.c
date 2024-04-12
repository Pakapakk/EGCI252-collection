#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// path to my_fifo
#define FIFO_NAME "/tmp/my_fifo"
// /tmp dir can be accessed by any users

int main(int argc, char *argv[]) {
  int res, open_mode = 0;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <[O_RDONLY, O_WRONLY, O_RDWR, O_NONBLOCK]>\n", *argv);
    exit(EXIT_FAILURE);
  }

  argv++;
  if (*argv) {
    if (strncmp(*argv, "O_RDONLY", 8) == 0)
      open_mode |= O_RDONLY;
    if (strncmp(*argv, "O_WRONLY", 8) == 0)
      open_mode |= O_WRONLY;
    if (strncmp(*argv, "O_RDWR", 6) == 0)
      open_mode |= O_RDWR;
    if (strncmp(*argv, "O_NONBLOCK", 10) == 0)
      open_mode |= O_NONBLOCK;
      // Neither the open() nor any subsequent I/O operations on
      // the file descriptor which is returned will cause the
      // calling process to wait.
  }

  if(access(FIFO_NAME, F_OK) == -1) {  // if FIFO DNE
    res = mkfifo(FIFO_NAME, 0777);  // create named pipe and give it full perm
    if (res) {
      fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
      exit(EXIT_FAILURE);
    }
  }

  printf("Process %d opening FIFO\n", getpid());
  res = open(FIFO_NAME, open_mode);  // open fifo
  printf("Process %d result %d\n", getpid(), res);
  // put your code here
  sleep(5);

  if (res != -1) (void)close(res);
  printf("Process %d finished\n", getpid());
  unlink(FIFO_NAME);  // unlink the named pipe
  exit(EXIT_SUCCESS);
}