#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Hello ");
  fork();
  printf("CS202\n");
}
