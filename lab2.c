#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  while (1) {
    printf("Enter program to run.\n");
    printf("> ");

    char *line = NULL;
    size_t len = 0;

    ssize_t nread = getline(&line, &len, stdin);

    if (nread != -1) {
      line[nread - 1] = '\0';

      pid_t pid = fork();

      if (pid == -1) {
        printf("Fork error\n");
        free(line);
        exit(EXIT_FAILURE);
      }

      if (pid == 0) {
        if (execlp(line, line, NULL) == -1) {
          printf("Exec failure\n");
          exit(EXIT_FAILURE);
        }
      } else {
        pid_t wait_id = waitpid(pid, NULL, 0);

        if (wait_id == -1) {
          printf("Error waiting for PID\n");
        }
      }

    } else {
      printf("Getline error\n");
      exit(EXIT_FAILURE);
    }
    free(line);
  }
  return 0;
}
