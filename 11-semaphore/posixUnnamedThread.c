/* Running with “./thunnamed”*/

#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PAUSE_TIME 800

sem_t mysem;

void *thread_func(void *arg) {
  char *op_char = (char *)arg;  // type casting
  for (int i = 0; i < 10; i++) {
    if (sem_wait(&mysem) == -1) exit(EXIT_FAILURE);  // lock

    // Begining of the critical section
    printf("[%c", *op_char);
    fflush(stdout);
    usleep(PAUSE_TIME);
    printf("%c]", *op_char);
    fflush(stdout);
    // End of the critical section

    if (sem_post(&mysem) == -1) exit(EXIT_FAILURE);  // unlock
  }
}

int main() {
  pthread_t tid1, tid2;
  char op_char1 = 'O'; 
  char op_char2 = 'X';

  sem_init(&mysem, 0, 1);  // init / pshared = 0 for sharing between threads / initValue = 1 for unlock

  pthread_create(&tid1, NULL, thread_func, &op_char1);  // for O
  pthread_create(&tid2, NULL, thread_func, &op_char2);  // for X

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  sem_destroy(&mysem);  // destroy
  printf("\nDone!\n");

  exit(EXIT_SUCCESS);
}