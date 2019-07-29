#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
  pid_t pid;
  int number;

  if ((pid = fork()) == 0)
  {
    number = atoi(argv[1]);
    if (number <= 0)
    {
      puts("Invalid number. Positive int expected.");
      return 1;
    }

    printf("%d", number);
    while (number != 1)
    {
      if (number % 2 == 0)
        number /= 2;
      else
        number = number*3 + 1;
      printf(", %d", number);
    }
    putchar('\n');
  }
  else
  {
    wait(NULL);
    return 0;
  }
}
