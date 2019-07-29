#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int total;
void *sum(void *);

int main(int argc, char **argv)
{
  pthread_t tid;
  pthread_attr_t tattr;

  pthread_attr_init(&tattr);

  pthread_create(&tid, &tattr, sum, argv[1]);
  pthread_join(tid, NULL);
  printf("%d\n", total);


  return 0;
}

void *sum(void *arg)
{
  int num = atoi(arg);
  int i;
  for (i = 0; i <= num; i++)
    total += i;
  pthread_exit(0);
}
