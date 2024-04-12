// Sender.c
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define Q_NAME "/my_mq"
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
  unsigned int priority = 0;
  char buffer[BUF_SIZE], *s;
  struct timespec to;  // need this struct for timer

  // attr init
  q_attr.mq_maxmsg = MAX_MSG;
  q_attr.mq_msgsize = MAX_MSG_SIZE;

  mqd = mq_open("/my_mq", O_WRONLY | O_CREAT, 0660, &q_attr);  // open with perm and attr
  if (mqd == -1) {
    perror("mq_open failed ");
    exit(EXIT_FAILURE);
  }

  while (running) {
    printf("Enter data: ");
    s = fgets(buffer, BUF_SIZE, stdin);
    printf("Size of msgs: %lu\n", sizeof(struct msgs));
    strcpy(a_msg.data, buffer);
    clock_gettime(CLOCK_REALTIME, &to); // get the current time and store in struct
    to.tv_sec += 5;  // make it timeout in 5 second from now
    if (mq_timedsend(mqd, (void *)&a_msg, sizeof(struct msgs), priority, &to) ==
        -1) {
      perror("mq_timedsend failed ");
      // exit(EXIT_FAILURE);
    }
    if (strncmp(buffer, "end", 3) == 0)
      running = 0;
  }

  mq_close(mqd);
  exit(EXIT_SUCCESS);
}