#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Before fork, my PID is %d\n", getpid());
  int ret = fork();
  printf("fork returns %d, my PID is %d\n", ret, getpid());
}
