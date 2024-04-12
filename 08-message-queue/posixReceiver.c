// Receiver.c
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define Q_NAME "/pos_msgQ"
#define Q_PERM 0660
#define MAX_MSG 3
#define MAX_MSG_SIZE 256
#define BUF_SIZE 60

struct msgs {
  int written;
  char data[BUF_SIZE];
};

int main(void) {
  int running = 1;
  struct msgs a_msg;
  struct mq_attr q_attr;
  mqd_t mqd;
  unsigned int priority = 0; // important

  // attr init
  q_attr.mq_maxmsg = MAX_MSG;
  q_attr.mq_msgsize = MAX_MSG_SIZE;

  mqd = mq_open(Q_NAME, O_RDONLY | O_CREAT, 0660, &q_attr);
  if (mqd == -1) {
    perror("mq_open failed ");
    exit(EXIT_FAILURE);
  }

  while (running) {
    if (mq_receive(mqd, (void *)&a_msg, MAX_MSG_SIZE, &priority) == -1) {  //priority for receive need to be the reference
      perror("mq_receive failed ");
      exit(EXIT_FAILURE);
    }
    printf("Received Message: %s", a_msg.data);
    if (strncmp(a_msg.data, "end", 3) == 0)
      running = 0;
  }
  mq_close(mqd);  // close the posix msgQ
  if (mq_unlink(Q_NAME) == -1) { //unlink posix msgQ
    perror("mq_unlink failed ");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}