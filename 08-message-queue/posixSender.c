// Sender.c
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// dir name for posix msgQ (can be any name but "/" is needed in the front)
#define Q_NAME "/pos_msgQ"
#define Q_PERM 0660
#define MAX_MSG 3
#define MAX_MSG_SIZE 256
#define BUF_SIZE 60

struct msgs {
  int written;  // posix no need to use long here
  char data[BUF_SIZE];
};

int main(void) {
  int running = 1;
  struct msgs a_msg;
  struct mq_attr q_attr;  // must provide this attr struct
  mqd_t mqd;  // use for posix msgQ ID data type
  unsigned int priority = 0;  // use this instead of long msg_type
  char buffer[BUF_SIZE], *s;

  // attr init
  q_attr.mq_maxmsg = MAX_MSG;
  q_attr.mq_msgsize = MAX_MSG_SIZE;

  mqd = mq_open(Q_NAME, O_WRONLY | O_CREAT, 0660, &q_attr);
  if (mqd == -1) {
    perror("mq_open failed ");
    exit(EXIT_FAILURE);
  }

  while (running) {
    printf("Enter data: ");
    s = fgets(buffer, BUF_SIZE, stdin);  
    printf("Size of msgs: %lu\n", sizeof(struct msgs));
    strcpy(a_msg.data, buffer);
    if (mq_send(mqd, (void *)&a_msg, sizeof(struct msgs), priority) == -1) {  // send must contain sizeof struct and priority value
      perror("mq_send failed ");
      exit(EXIT_FAILURE);
    }
    if (strncmp(buffer, "end", 3) == 0)
      running = 0;
  }

  mq_close(mqd);
  exit(EXIT_SUCCESS);
}