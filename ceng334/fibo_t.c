#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_SIZE 100

void *fibo(void*);
int num;
int nums[MAX_SIZE];

int main(int argc, char **argv)
{
  int i;
  pthread_t tid;
  pthread_attr_t attr;
  num = atoi(argv[1]);

  pthread_attr_init(&attr);
  pthread_create(&tid, &attr, fibo, NULL);
  pthread_join(tid, NULL);
  for (i = 0; i < num; i++)
    printf("%d\n", nums[i]);

  return 0;
}

void *fibo(void *v)
{
  int i;
  nums[0] = nums[1] = 1;
  for (i = 2; i < num; i++)
    nums[i] = nums[i-1] + nums[i-2];

  pthread_exit(0);
}
