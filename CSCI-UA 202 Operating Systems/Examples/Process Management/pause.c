#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handler(int sig) {
}

int main() {
  signal(SIGINT, handler);
  printf("Press Ctrl-C to continue...\n");
  pause();
  printf("...Adiós!\n");
}
