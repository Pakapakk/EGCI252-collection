#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  FILE *read_fp;
  char buffer[BUFSIZ + 1];
  int chars_read;

  memset(buffer, '\0', sizeof(buffer));
  read_fp = popen("uname -a", "r");  
  // uname -a -> OS name with details such as version, release date, hardware name and processor type.
  if (read_fp != NULL) {
    chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
    if (chars_read > 0) {
      printf("Output from pipe: \n%s\n", buffer);
    }
    pclose(read_fp);
    exit(EXIT_SUCCESS);
  }
  exit(EXIT_FAILURE);
}