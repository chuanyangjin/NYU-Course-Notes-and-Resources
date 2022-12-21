#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig) {
  printf("...Ouch!\n");
}

int main() {
  signal(SIGINT, handler);
  for (int i = 0; ; ++i) {
    printf("%d\n", i);
    sleep(1);
  }
}
