// gcc -o run G5P1.c -lm
// ./run

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
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define maxThread 5
//#define maxThread 1
#define upperBound 50000

int primeListFromThread[maxThread][upperBound / maxThread] = {0};
int primeCountInThread[maxThread] = {0};

typedef struct findPrimeParam findPrimeParam;
struct findPrimeParam {
    int a; int b; int threadNum;
};

void addPrimeToList(int n, int threadNum) {
    primeListFromThread[threadNum][primeCountInThread[threadNum]++] = n;
}

void * findPrimeFrom(void * parameters) {
    findPrimeParam * param = (struct findPrimeParam *) parameters;
    int a = param->a, b = param->b, threadNum = param->threadNum;
    int i; for(i=a; i<=b; i++) {
        if (i < 2) continue;
        int maxPossibleFactor = sqrt(i) + 1;
        int isPrime = 1;
        int j; for(j=2; j<=maxPossibleFactor; j++)
            if (i % j == 0) {
                isPrime = 0;
                break;
            }
        if (isPrime || i == 2) addPrimeToList(i, threadNum);
    }
}

int main() {

    pthread_t threadID[maxThread];
    findPrimeParam primeParam[maxThread];
    int i; for(i=0; i<maxThread; i++) {
        primeParam[i].a = i * (upperBound / maxThread);
        primeParam[i].b = (i + 1) * upperBound / maxThread - 1;
        primeParam[i].threadNum = i;
        pthread_create(&threadID[i], NULL, &findPrimeFrom, &primeParam[i]);
    }
    for(i=0; i<maxThread; i++)
        pthread_join(threadID[i], NULL);

    for(i=0; i<maxThread; i++){
        int j; for(j=0; j<primeCountInThread[i]; j++)
            printf("%d ", primeListFromThread[i][j]);
    }

    printf("\n");
}

/*
  time for 5 threads
    real    0m0.109s
    user    0m0.027s
    sys 0m0.018s

  time for 1 thread
    real    0m0.050s
    user    0m0.015s
    sys 0m0.021s
*/