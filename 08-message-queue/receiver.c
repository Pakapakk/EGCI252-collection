// receiver.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

// 1. init msg struct
struct a_msg {
  long int msg_type;
  char data[BUFSIZ];
};

int main(void) {
  int running = 1, msgID;
  struct a_msg a_msg;
  long int rcv_msg_type = 0;
  char buffer[BUFSIZ];

  msgID = msgget((key_t)1234, 0666 | IPC_CREAT); // 2. get msgID from msgget()

  if (msgID == -1) {
    fprintf(stderr, "msgget failed\n");
    exit(EXIT_FAILURE);
  }

  while (running) {
    if (msgrcv(msgID, (void *)&a_msg, BUFSIZ, rcv_msg_type, 0) == -1) { // 3. msgrcv() for receiving message
      fprintf(stderr, "msgrcv failed\n");
      exit(EXIT_FAILURE);
    }
    printf("Received Message: %s", a_msg.data);
    if (strncmp(a_msg.data, "end", 3) == 0)
      running = 0;
  }
  if (msgctl(msgID, IPC_RMID, 0) == -1) { // 4. msgctl to remove the msgQ
    fprintf(stderr, "msgctl failed\n");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}