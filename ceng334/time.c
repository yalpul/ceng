#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
int main(int argc, char **argv)
{
  pid_t pid;
  struct timeval start, end;

  printf("%d\n", gettimeofday(&start, NULL));
  pid = fork();

  if (pid == 0)
    execvp(argv[1], argv+1);
  wait(NULL);
  gettimeofday(&end, NULL);
  printf("%d\n", end.tv_usec-start.tv_usec);
  printf("%d\n", start.tv_usec);
  printf("%d\n", end.tv_usec);
  return 0;
}
