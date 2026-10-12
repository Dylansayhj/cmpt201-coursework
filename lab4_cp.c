#define _DEFAULT_SOURCE

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define HEAP_SIZE 256
#define BLOCK_SIZE 128
#define BUF_SIZE 100

struct header {
  unit64_t size;
  struct header *next;
};
void handle_error(char *m) {
  perror(m);
  exit(EXIT_FAILURE);
}

// use to divide the heap to each block
void initialize_block() {}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

int main() {
  char *start = sbrk(HEAP_SIZE);
  if (start == (void *)-1) {
    handle_error("sbrk");
  }
  struct header *first_block = (struct header *)start;
  // second block 128 byte after
  struct header *second = (struct header *)(start + BLOCK_SIZE);

  initialize_block(first_block_pointer);
  initailize_block(second_block_pointer);
  // May want to print as you go for debugging
  print_out(...);
}
