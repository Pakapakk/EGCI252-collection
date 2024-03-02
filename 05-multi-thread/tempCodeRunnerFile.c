#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

void *computePrime(void *arg)
{
    int candidate = 2, n = *((int *)arg);
    while (1){
        int factor, isPrime = 1;
        /* Test primality by successive division. */
        for (factor = 2; factor < candidate; ++factor){
            if (candidate % factor == 0){
                isPrime = 0;
                break;
            }
        }
        /* Is this the prime number we’re looking for? */
        if (isPrime){
            if (--n == 0)
                /* Return the desired prime number as the thread return value. */
                return (void *)candidate;
        }
        ++candidate;
    }
    return NULL;
}

int main(){
    pthread_t thread;
    int whichPrime = 5133, prime;

    pthread_create(&thread, NULL, &computePrime, (&whichPrime);
    pthread_join(thread, (void*)&prime);
    printf("The %dth prime is %d\n", whichPrime, prime);
}