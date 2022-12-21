#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Hello CS202\n");

  int fd = open("output.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
  dup2(fd, 1);  // duplicate the file descriptor
  close(fd);    // close the unused file descriptor

  printf("Hello CS202 again\n");
}
