#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  char *buffer;
  string str[] = "hello world";
  int fd_temp = open("tmp", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
  size_t count = 0;
  write(fd_temp, "hello world", strlen(str));
  lseek(fd_temp, buffer, 6);
  int s = read(fd_temp, buffer, 6);
  write(STDOUT_FILENO, buffer, 6);
  close(fd_temp);
  return;
}
