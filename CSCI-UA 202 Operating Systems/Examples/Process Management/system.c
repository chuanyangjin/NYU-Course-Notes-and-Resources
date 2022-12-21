#include <stdlib.h>
#include <stdio.h>

int main() {
  printf("Before system\n");
  system("ls");
  printf("After system\n");
}
