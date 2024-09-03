#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct char_print_params
{
    char ch;
    int count;
};

void* char_print(void* parameters)
{
    struct char_print_params* p = (struct char_print_params*) parameters;
    int i;
    for(i = 0; i < p->count; i++){
        fputc(p->ch, stderr);
    }
    return NULL;
}

int main(){
    pthread_t threadID1, threadID2;
    struct char_print_params threadArgs1;
    struct char_print_params threadArgs2;

    threadArgs1.ch = 'x';
    threadArgs1.count = 30000;
    pthread_create(&threadID1, NULL, &char_print, &threadArgs1);

    threadArgs2.ch = 'o';
    threadArgs2.count = 20000;
    pthread_create(&threadID2, NULL, &char_print, &threadArgs2);

    return 0;
}