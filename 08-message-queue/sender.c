// sender.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

// 1. init msg struct
struct a_msg {
  long int msg_type;  // important : the first data of the msg struct must be long data type
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
    printf("Enter data: ");
    fgets(buffer, BUFSIZ, stdin);  // get input from stdin and store in the buffer
    a_msg.msg_type = 1;  // 3. specify the msg_type and when receive, set the msg_type to be this value to get the msg from this process
    strcpy(a_msg.data, buffer);
    if (msgsnd(msgID, (void *)&a_msg, BUFSIZ, 0) == -1) {  // 4. msgsnd() to send the data to msgQ
      fprintf(stderr, "msgsnd failed\n");
      exit(EXIT_FAILURE);
    }
    if (strncmp(buffer, "end", 3) == 0)
      running = 0;
  }
  exit(EXIT_SUCCESS);
}