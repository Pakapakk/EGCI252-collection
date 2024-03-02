#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int num = atoi(argv[1]);
    int loops = atoi(argv[2]);
    int a;

    setbuf(stdout, NULL);
    for(int a = 0; a < loops; a++){
        printf("%d", num);
        //sleep(1);
    }
    printf("\n");
    return 0;
}