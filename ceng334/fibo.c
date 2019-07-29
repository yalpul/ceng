#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
  pid_t pid;
  int number = atoi(argv[1]);
  if (number <= 0)
  {
    puts("Invalid number. Positive int expected.");
    return 1;
  }

  if ((pid = fork()) == 0)
  {
    int num1 = 1, num2 = 1, i;
    for (i = 1; i < number; i++)
    {
      int tmp = num2;
      printf("%d\n", num1);
      num2 += num1;
      num1 = tmp;
    }
    printf("%d\n", num1);
    printf("%d\n", num2);
  }
  else
    wait(NULL);

  return 0;
}
