#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
  pid_t pid = fork();
  if (pid == 0) {
    if (execlp("ls", "-a", "-l", NULL) == -1) {
      perror("execl");
      exit(EXIT_FAILURE);
    }
  } else {
    int wstatus = 0;
    if (waitpid(pid, &wstatus, 0) == -1) {
      perror("waitpid");
      exit(EXIT_FAILURE);
    }
    if (WIFEXITED(wstatus)) {
      printf("child done with exit status: %d\n", WEXITSTATUS(wstatus));
    } else
      printf("child not exit normally");
  }
}
