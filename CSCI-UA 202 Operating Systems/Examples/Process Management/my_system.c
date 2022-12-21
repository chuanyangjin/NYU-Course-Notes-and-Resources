#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int my_system(const char *command) {
  if (fork() == 0) {
    execl("/bin/sh", "/bin/sh", "-c", command, NULL);
    exit(-1);
  }
  return 0;
}

int main() {
  printf("Before system\n");
  my_system("ls");
  printf("After system\n");
}
