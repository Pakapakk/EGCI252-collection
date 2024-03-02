#include <stdio.h>
#include <unistd.h>

int main(void){
  printf("Starting in the foo.c\n");
  f1();
  f2();
  return 0;
}


// to run this 
// gcc -c foo.c part1.c part2.c
// gcc -o foo foo.o part1.o part2.o
// ./foo

// make part1.c and part2.c as the lib.a -- static library
// ar crv lib.a part1.o part2.o
// gcc -o foo foo.c lib.a

// make the shared lib
// gcc -c part1.c part2.c 
// gcc -fpic -shared -o sfoo.so part1.o part2.o
// gcc -fpic -shared -o sfoo.so part1.c part2c    --- (combine 2 previous steps)
// gcc -o sfoo foo.c sfoo.so
// export LD_LIBRARY_PATH=.
// ./sfoo