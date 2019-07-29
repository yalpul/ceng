#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>

const int SIZE = 4096;

int main(int argc, char **argv)
{
  pid_t pid;
  int number, fd, i;
  int *buf;

  fd = shm_open("shm", O_CREAT | O_RDWR, 0666);
  ftruncate(fd, SIZE);

  if ((pid = fork()) == 0)
  {
    buf = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    number = atoi(argv[1]);
    if (number <= 0)
    {
      puts("Invalid number. Positive int expected.");
      buf[0] = -1;
      return 1;
    }
    i = 0;
    while (number != 1)
    {
      buf[i++] = number;
      if (number % 2 == 0)
        number /= 2;
      else
        number = number*3 + 1;
    }
    buf[i] = number;

    shm_unlink("shm");
  }
  else
  {
    buf = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    wait(NULL);
    if (buf[0] == -1)
      return 1;
    for (i = 0; buf[i] != 1; i++)
      printf("%d, ", buf[i]);
    puts("1");
  }
  return 0;
}
