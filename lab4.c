
#define _DEFAULT_SOURCE
#define _ISOC99_SOURCE

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HEAP_SIZE 256
#define BLOCK_SIZE 128
#define BUF_SIZE 100

struct header {
  uint64_t size;
  struct header *next;
};

void handle_error(char *m) {
  perror(m);
  exit(EXIT_FAILURE);
}

void initialize_block(struct header *block, uint64_t size, struct header *next, int fill_value) {
  block->size = size;
  block->next = next;
  memset((char *)(block + 1), fill_value, size - sizeof(struct header));
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  int len;

  if (data_size == sizeof(uint64_t)) {
    len = snprintf(buf, BUF_SIZE, format, *(uint64_t *)data);
  } else {
    len = snprintf(buf, BUF_SIZE, format, *(void **)data);
  }

  if (len < 0) {
    handle_error("snprintf");
  }

  if (len >= BUF_SIZE) {
    len = BUF_SIZE - 1;
  }

  write(STDOUT_FILENO, buf, (size_t)len);
}

void print_block(char *start) {
  for (int i = 0; i < BLOCK_SIZE - sizeof(struct header); ++i) {
    char *addr = start + sizeof(struct header) + i;
    uint64_t val = (unsigned char)*addr;
    print_out("%lu\n", &val, sizeof(val));
  }
}

int main(void) {
  char *start = sbrk(0);

  if (sbrk(HEAP_SIZE) == (void *)-1) {
    handle_error("sbrk");
  }

  struct header *first_block = (struct header *)start;
  struct header *second = (struct header *)(start + BLOCK_SIZE);

  initialize_block(first_block, BLOCK_SIZE, second, 0);
  initialize_block(second, BLOCK_SIZE, NULL, 0);

  print_out("first block: %p\n", &first_block, sizeof(first_block));
  print_out("second block: %p\n", &second, sizeof(second));

  print_out("first block size: %lu\n", &first_block->size, sizeof(first_block->size));
  print_out("first block next: %p\n", &first_block->next, sizeof(first_block->next));

  print_out("second block size: %lu\n", &second->size, sizeof(second->size));
  print_out("second block next: %p\n", &second->next, sizeof(second->next));

  print_block((char *)first_block);

  return 0;
}
