#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  FILE *fp = fopen("file.txt", "w");

  pid_t pid = fork();
  for (int i = 0; i < 5; ++i) {
    fprintf(fp, "[%d] %d\n", getpid(), i);
    fflush(fp);
    sleep(rand() % 2);
  }
  fclose(fp);

  if (pid)
    wait(NULL);
}
