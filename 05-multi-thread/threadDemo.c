#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* printX(void* unused)
{
    int n;
    printf("n_x = %x\n", &n);
    for(n = 100; n > 0; n--){
        fputc('X', stderr); usleep(1);
    }
    return NULL;
}

void* printY(void* unused)
{
    int n;
    printf("n_y = %x\n", &n);
    for(n = 100; n > 0; n--){
        fputc('Y', stderr); usleep(1);
    }
    return NULL;
}

int main(){
    int n;
    printf("\nn_x = %x\n", &n);
    pthread_t threadID1, threadID2;

    pthread_create(&threadID1, NULL, &printX, NULL);
    pthread_create(&threadID2, NULL, &printX, NULL);

    for(n = 100; n > 0; n--){
        fputc('Z', stderr); usleep(1);
    }
    return 0;
}
