#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <math.h>

int arr[10] = {1, 3, 4, 5, 6, 7, 8, 9 ,10, 11};

void * sumArr(void *args){
  int index = *((int *)args);  //point args to the index is the first arg of the array
  int sum = 0;
  
  for(int i = 0; i < 5; i++){
    sum += arr[index + i];
  }
  printf("Local sum = %d\n", sum);
  *((int *)args) = sum;
  
  return args;
}

int main(){
  pthread_t threadID[2];

  for(int i = 0; i < 2; i++){
    int *threadArgs = malloc(sizeof(int));
    *threadArgs = i * 5;
    //int threadArgs = i * 5; // bug
    pthread_create(&threadID[i], NULL, &sumArr, threadArgs);
  }

  int globalSum = 0;
  for(int i = 0; i < 2; i++){
    int *result;
    pthread_join(threadID[i], (void**) &result);
    globalSum += *result;
    free(result);
  }
  printf("Global sum = %d\n", globalSum);
  return 0;
}
