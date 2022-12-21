#include <stdio.h>
#include <unistd.h>

int main() {
  if (fork() == 0) {
    // child process
    printf("My parent's PID is %d\n", getppid());
    sleep(2);
    printf("My parent's PID is %d\n", getppid());
  } else {
    // parent process
    sleep(1);
  }
  // both processes
  printf("Terminated\n");
}
