#include <stdio.h>

int main(void)
{
  int c;
  FILE *in, *out;

  in = fopen("file.in", "r");
  out = fopen("file.out", "w");
    
  while ((c = getc(in)) != EOF)
      putc(c, out);
   
  fclose(in);
  fclose(out);
  return 0;
}