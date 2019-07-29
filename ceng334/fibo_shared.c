#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define MAX_SIZE 100

typedef struct {
  int numbers[MAX_SIZE];
  int count;
} shared_data;

int main(int argc, char **argv)
{
  int number = atoi(argv[1]), i;
  int fd = shm_open("shm", O_CREAT | O_RDWR, 0666);
  pid_t pid;
  shared_data *sd;
  ftruncate(fd, MAX_SIZE*sizeof(int));

  if (number <= 0)
  {
    puts("Invalid number. Positive int expected.");
    return 1;
  }

  if ((pid = fork()) == 0)
  {
    int num1 = 1, num2 = 1;
    sd = mmap(0, MAX_SIZE*sizeof(int), PROT_WRITE, MAP_SHARED, fd, 0);
    sd->count = number+1;
    for (i = 0; i < number - 1; i++)
    {
      int tmp = num2;
      sd->numbers[i] = num1;
      num2 += num1;
      num1 = tmp;
    }
    sd->numbers[i++] = num1;
    sd->numbers[i] = num2;

    shm_unlink("shm");
  }
  else
  {
    sd = mmap(0, MAX_SIZE*sizeof(int), PROT_READ, MAP_SHARED, fd, 0);
    wait(NULL);
    for (i = 0; i < sd->count; i++)
      printf("%d\n", sd->numbers[i]);
  }

  return 0;
}
