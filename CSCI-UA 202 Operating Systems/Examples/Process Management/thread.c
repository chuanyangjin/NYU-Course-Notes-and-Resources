#include <pthread.h>
#include <stdio.h>

void *greet(void *name) {
  printf("Hello, %s!\n", (char *)name);
  pthread_exit(NULL);
}

int main() {
  pthread_t tid;
  pthread_create(&tid, NULL, greet, "world");
  printf("I am still running...\n");
  pthread_join(tid, NULL);
}
