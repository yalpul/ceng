#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int num;
int inside;
int total;

void *calc_pi(void*);

int main(int argc, char **argv)
{
  pthread_t tid;
  pthread_attr_t attr;

  num = atoi(argv[1]);
  pthread_attr_init(&attr);
  pthread_create(&tid, &attr, calc_pi, NULL);
  pthread_join(tid, NULL);
  printf("%f\n", 4.0*inside/total);

  return 0;
}

void *calc_pi(void *v)
{
  int i;
  double x, y;
  srand(time(NULL));
  for (i = 0; i < num; i++)
  {
    x = (double)rand() / RAND_MAX;
    y = (double)rand() / RAND_MAX;
    x = 2*x - 1.0;
    y = 2*y - 1.0;
    if (x*x + y*y <= 1.0)
      inside++;
    total++;
  }
  pthread_exit(0);
}
