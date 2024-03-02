#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
    if((write(1, "Some data is written\n", 21)) != 21){  // standard output
        write(2, "An error has occurred on the stdout\n", 36);  // standard error
    }
    return 0;
}