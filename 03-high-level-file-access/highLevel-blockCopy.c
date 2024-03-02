#include <stdio.h>

int main(void)
{
  char block[512];
  FILE *in, *out;

  in = fopen("file.in", "r");
  out = fopen("file.out", "w");
  while (fgets(block, sizeof(block), in) != NULL)
      fputs(block, out);
     
  return 0;
}