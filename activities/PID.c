#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main() {

  printf("PID= %d, parent PID= %d\n", getpid(), getppid());
  pid_t pid = fork();
  if (pid != 0) {
    printf("parent= %d, child PID= %d\n", getpid(), pid);
  } else {
    printf("child= %d, parent PID= %d\n", getpid(), getppid());
  }
  return 0;
}
