#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
char *history[5];
int count = 0;
void *get_user_input() {
  char *buff = NULL;
  size_t size = 0;
  printf("ENTER input: ");
  size_t len = getline(&buff, &size, stdin);
  if (len == -1) {
    exit(1);
  }
  buff[len - 1] = '\0';
  return buff;
}

void print_result() {
  for (int i = 0; i < count; i++) {
    printf("%s\n", history[i]);
  }
}
void free_history();
void add_to_history(char *input) {
  if (count >= 5) {

    free_history();
  }
  history[count] = input;
  count++;
}
void free_history() {
  if (count >= 0) {
    free(history[0]);
    for (int i = 1; i < count; i++) {
      history[i - 1] = history[i];
    }
    count--;
  }
}
int main() {
  while (1) {
    char *input = get_user_input();
    add_to_history(input);
    if (strcmp(input, "print") == 0) {
      print_result();
    }
  }
  return 0;
}
