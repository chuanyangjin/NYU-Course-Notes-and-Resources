#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Before fork, my PID is %d\n", getpid());
  fork();
  printf("After fork, my PID is %d\n", getpid());
}
