// Receiver.c
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

// struct mq_attr {
//   long mq_flags; /* Flags 0 or O_NONBLOCK (ignored for mq_open()) */
//   long mq_maxmsg; /* Max. # of messages on queue */
//   long mq_msgsize; /* Max. message size (bytes) */
//   long mq_curmsgs; /* # of messages currently in queue (ignored for mq_open()) */
// };

int main(void) {
  int running = 1;
  struct msgs a_msg;
  struct mq_attr q_attr;
  mqd_t mqd;
  unsigned int priority = 0;
  struct timespec to;

  q_attr.mq_maxmsg = MAX_MSG;
  q_attr.mq_msgsize = MAX_MSG_SIZE;

  mqd = mq_open("/my_mq", O_RDONLY | O_CREAT, 0660, &q_attr); // open msgQ with attr struct
  if (mqd == -1) {
    perror("mq_open failed ");
    exit(EXIT_FAILURE);
  }

  while (running) {
    clock_gettime(CLOCK_REALTIME, &to);  // Retrieve the time of the specified clock
    to.tv_sec += 15;  // set timeout to be 15 second from the current time
    if (mq_timedreceive(mqd, (void *)&a_msg, MAX_MSG_SIZE, &priority, &to) == -1) { // receive 
      perror("mq_timedreceive failed ");
      exit(EXIT_FAILURE);
    }
    printf("Received Message: %s", a_msg.data);
    if (strncmp(a_msg.data, "end", 3) == 0)
      running = 0;
  }
  mq_close(mqd);  // close
  if (mq_unlink(Q_NAME) == -1) {  // unlink when done
    perror("mq_unlink failed ");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}