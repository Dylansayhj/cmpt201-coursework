#define _POSIX_C_SOURCE 1993010
#define _GNU_SOURCE
#include <pthread.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int cnt =0;
void *thread_func(void *arg) {
  char *msg = arg;
  printf("In thread %d: %s\n", gettid(), msg);
  sleep(1);
  printf("Thread done\n");
  return (void *)strlen(msg);
}

int main(void) {
  pthread_t new_thread;
  if (pthread_create(&new_thread, NULL, thread_func, "Hello world") != 0) {
    perror("Unable to create thread.");
    exit(1);
  }
  void *ret_val = 0;
  if (pthread_join(new_thread, &ret_val) != 0) {
  }
  uint64_t retVAl = (uint64_t)ret_val;
  printf("%lu", (uint64_t)retVAl);
  printf("DONE\n");


  return 0;
}
