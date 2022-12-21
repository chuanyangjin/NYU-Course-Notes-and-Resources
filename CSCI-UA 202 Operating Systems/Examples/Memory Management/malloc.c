#include <stdlib.h>
#include <stdio.h>

int main() {
  char *ptr1 = malloc(24);
  char *ptr2 = malloc(24);
  printf("The distance between ptr1 and ptr2 is %ld bytes\n", ptr2 - ptr1);
}
