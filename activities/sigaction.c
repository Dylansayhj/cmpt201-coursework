#define _POSIX_C_SOURCE 1993010
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void sig_handler(int a) { write(STDOUT_FILENO, "CTRL-C Pressed \n", 14); }

int main() {
  struct sigaction sig_name;
  sig_name.sa_handler = sig_handler;
  sig_name.sa_flags = 0;
  sigemptyset(&sig_name.sa_mask);
  if (sigaction(SIGINT, &sig_name, NULL) == -1) {
    perror("sigaction fail\n");
    exit(EXIT_FAILURE);
    printf("Parent is now dozing...\n");
    while (1) {
      sleep(1);
    }
  } else {
    while (1) {
      sleep(2);
      printf("signal for parents\n");
      if (kill(getppid(), SIGIT) == -1) {
        perror("unable to send signal to parent.");
        exit(EXIT_FAILURE);
      }
    }
  }
}
