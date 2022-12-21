#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Before exec\n");
  execl("/bin/ls", "/bin/ls", NULL);
  printf("After exec\n");
}
