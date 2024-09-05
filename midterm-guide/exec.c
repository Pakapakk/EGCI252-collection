#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

int main() {
    int pid = fork();

    if (pid == -1) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) { // child
      // char *argvForExecv[] = {"cat", "/etc/passwd", NULL};
      int stat = execl("/bin/ls", "ls", "-l", NULL);
      // int stat = execv("/bin/cat", argvForExecv);
      if (stat == -1) {
            perror("execl failed");
            return 2;
        }
    } else { // parent
        int status;
        //waitpid(pid, &status, 0); // Wait for the child process
        wait(&status);
        if (WIFEXITED(status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        }
    }
    return 0;
}