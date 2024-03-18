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
// struct for parameters
struct findPrimeParam {
    int a; // parameter lower bound
    int b; // parameter upper bound
    int threadNum; // thread number
};

// shortcut for adding prime numbers to the list [parameter needed : index(n) and thread number(threadNum)]]
void addPrimeToList(int n, int threadNum) {
    primeListFromThread[threadNum][primeCountInThread[threadNum]++] = n;
}

//function to check if a number is prime and add it to the list
void * findPrimeFrom(void * parameters) {
    findPrimeParam * param = (struct findPrimeParam *) parameters;
    int a = param->a, b = param->b, threadNum = param->threadNum;
    // begin calculate prime
    int i; for(i=a; i<=b; i++) {
        if (i < 2) continue;
        int maxPossibleFactor = sqrt(i) + 1;
        int isPrime = 1;
        int j; for(j=2; j<=maxPossibleFactor; j++)
            if (i % j == 0) {
                isPrime = 0;
                break;
            }
        // if it is prime add it to the array
        if (isPrime || i == 2) addPrimeToList(i, threadNum);
    }
}

int main() {
    pthread_t threadID[maxThread];
    findPrimeParam primeParam[maxThread];
    // creatig threads
    int i; for(i=0; i<maxThread; i++) {
        primeParam[i].a = i * (upperBound / maxThread);
        primeParam[i].b = (i + 1) * upperBound / maxThread - 1;
        primeParam[i].threadNum = i;
        pthread_create(&threadID[i], NULL, &findPrimeFrom, &primeParam[i]);
    }
    // joining threads
    for(i=0; i<maxThread; i++)
        pthread_join(threadID[i], NULL);

    // print all results
    for(i=0; i<maxThread; i++){
        int j; for(j=0; j<primeCountInThread[i]; j++)
            printf("%d ", primeListFromThread[i][j]);
    }

    printf("\n");
}

/*
  time for 5 threads
    real    0m0.037s
    user    0m0.027s
    sys 0m0.014s

  time for 1 thread
    real    0m0.041s
    user    0m0.017s
    sys 0m0.023s

In the case of 5 threads, the time is faster than using 1 thread as we can see in the real and sys section of both outputs
*/