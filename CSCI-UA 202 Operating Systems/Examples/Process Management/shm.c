#include <stdio.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  // create a 4-byte shared memory
  int *count = mmap(NULL, 4, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  pid_t pid = fork();

  for (int i = 0; i < 1000000; ++i) {
    ++*count;
  }

  if (pid) {
    wait(NULL);
    printf("count = %d\n", *count);
  }
}
