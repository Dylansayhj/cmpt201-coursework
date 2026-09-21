#define _POSIX_C_SOURCE 200809L // needed to get getline() and strtok_r() declarations

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  printf("Please enter some text: ");
  char *buffer = NULL;
  size_t size = 0;
  if (getline(&buffer, &size, stdin) != -1L) {
    char *string_input = buffer;
    char *delim = " \t\n\r";
    char *token = NULL;
    char *saveptr = NULL;
    printf("token:\n");
    while ((token = strtok_r(string_input, delim, &saveptr))) {
      printf("%s\n", token);
      string_input = NULL;
    }
  } else {
    printf("Getline failure.\n");
  }
  free(buffer);
}
