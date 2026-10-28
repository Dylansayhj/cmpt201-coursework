#define _POSIX_C_SOURCE 1993010
#define _GNU_SOURCE
#include <pthread.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int cnt = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static void *count_upward(void *arg) {
  for (int i = 0; i < 10000000; i++) {
    pthread_mutex_lock(&mutex);
    cnt++;
    pthread_mutex_unlock(&mutex);
  }
  pthread_exit(0);
}
int main() {
  pthread_t thread_1, thread_2;
  pthread_create(&thread_1, NULL, count_upward, NULL);
  pthread_create(&thread_2, NULL, count_upward, NULL);
  pthread_join(thread_1, NULL);
  pthread_join(thread_2, NULL);

  printf("%d", cnt);
  return 0;
}
