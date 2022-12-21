#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  int pid;
  if ((pid = fork()) != 0) {
    printf("Look at Process %d...", pid);
    getchar();  // Press ENTER to continue
    wait(NULL);
    printf("Look again!");
    getchar();  // Press ENTER to continue
  }
}
