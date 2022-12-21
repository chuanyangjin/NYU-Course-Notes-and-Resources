#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Hello ");
  fflush(stdout);
  fork();
  printf("CS202\n");
}
