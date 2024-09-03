# 05 - Multi Threads
## Definition
Multithreads programming is the method allowing system to do more than one thing at a time as threads appear to run `concurrently`.

## Threads vs Processes
| Thread | Process |
| ------ | ------- |
| - run the same function | - may run different functions
| - share virtual memory resources | - copy program's memory space |
| - concurrency | - parallelism |

## Libraries used
- `#include <pthread.h>`

## Thread Creation
`int pthread_create(pthread_t *restrict thread_id, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg);`

ps, we often leave the last parameter as `NULL`

```c
pthread_create(&threadID1, NULL, &func, NULL);
```

## Thread Exit
A thread can alternatively exit explicitly by calling `void pthread_exit(void* exitValue)` instead of returning from the thread function..
```c
int *return;
pthread_create(return);
```

## Parsing Data to Threads
We cannot directly parse multiple parameters into the thread arguement in one go. Thus we can parse them as a `pointer to the structure` containing those parameters.
```c
// parameters structure
struct char_print_params
{
    char ch;
    int count;
};

void* char_print(void* parameters)
{
    struct char_print_params* p = (struct char_print_params*) parameters;
    // the rest of the code goes here
}

int main(){
    pthread_t threadID1;
    struct char_print_params threadArgs1;

    threadArgs1.ch = 'x';
    threadArgs1.count = 30000;
    pthread_create(&threadID1, NULL, &char_print, &threadArgs1);

    return 0;
}
```
## Joining Threads
Joining is the method that force program to wait until the specific thread finish its job using `int pthread_join(pthread_t threadID, void** threadReturnVal)`. If thread does not return the value, we shall put `NULL`.
```c
int main(){
    // the rest of the code goes here
    pthread_create(&threadID1, NULL, &char_print, &threadArgs1);

    pthread_join(threadID1, NULL);
    return 0;
}
```

## Thread Return Values
`int pthread_join(pthread_t threadID, void** threadReturnVal)`. f the value in the second argument of pthread_join is non-null, the return value of the thread will be store in that variable. The return type is void* like the thread argument type.
```c
void *computePrime(void *arg){
    // the rest of the code goes here
}

int main(){
    // the rest of the code goes here
    int prime;

    pthread_create(&thread, NULL, &computePrime, &whichPrime);
    pthread_join(thread, (void *)&prime);
    // the rest of the code goes here
}
```

## Thread Attributes


## Detach State
## Thread Cancallation
## Critical Section
## Race Condtions