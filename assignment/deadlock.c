/*
Leader - group representative
- 6481328 Pakapak Jungjaroen
Worker
- 6481145 Yanaput Makbonsonglop
- 6481331 Andaman Jamprasitsakul
Presenter
- 6481322 Mark Kittiphat Kuprasertwong
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>

static void f1();
static void f2();

union semun{
  int val;
  struct semid_ds *buf;
  unsigned short *array;
};

static int semID1;
static int semID2;
int pid;

static int set_semvalue(int semID) {
  union semun sem_union;
  sem_union.val = 1;
  if (semctl(semID, 0, SETVAL, sem_union) == -1)
    return (0);
  return (1);
}

static void del_semvalue(int semID) {
  union semun sem_union;

  if (semctl(semID, 0, IPC_RMID, sem_union) == -1)
    fprintf(stderr, "Failed to delete semaphore\n");
}

static int semaphore_lock(int semID) {
  struct sembuf sem_b;

  sem_b.sem_num = 0;
  sem_b.sem_op = -1; /* P() */
  sem_b.sem_flg = SEM_UNDO;
  if (semop(semID, &sem_b, 1) == -1) {
    fprintf(stderr, "semaphore_lock failed\n");
    return (0);
  }
  return (1);
}

static int semaphore_unlock(int semID) {
  struct sembuf sem_b;
  sem_b.sem_num = 0;
  sem_b.sem_op = 1; /* V() */
  sem_b.sem_flg = SEM_UNDO;
  if (semop(semID, &sem_b, 1) == -1) {
    fprintf(stderr, "semaphore_unlock failed\n");
    return (0);
  }
  return (1);
}

static void f1(int pid){
  semaphore_lock(semID1);
  if(pid) f2(pid);
  semaphore_unlock(semID1);
}

static void f2(int pid){
  semaphore_lock(semID2);
  if(!pid) f1(pid);
  semaphore_unlock(semID2);
}

int main(){
  semID1 = semget((key_t)123, 1, 0666 | IPC_CREAT);
  semID2 = semget((key_t)321, 1, 0666 | IPC_CREAT);
  
  pid = fork();
  if(pid){
    f1(pid);
  } else{
    f2(pid);
  }
  printf("Done!\n");
  exit(EXIT_SUCCESS);
}