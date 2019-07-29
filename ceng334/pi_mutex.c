#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define THREAD_NUM 8

int num;
int inside;
int total;

void *calc_pi(void*);
pthread_mutex_t inside_mutex, total_mutex;

int main(int argc, char **argv)
{
  int i;
  pthread_t tids[THREAD_NUM];
  pthread_attr_t attr;

  num = atoi(argv[1]);
  pthread_attr_init(&attr);
  pthread_mutex_init(&inside_mutex, NULL);
  pthread_mutex_init(&total_mutex, NULL);

  for (i = 0; i < THREAD_NUM; i++)
    pthread_create(&tids[i], &attr, calc_pi, NULL);

  for (i = 0; i < THREAD_NUM; i++)
    pthread_join(tids[i], NULL);
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
    {
      pthread_mutex_lock(&inside_mutex);
      inside++;
      pthread_mutex_unlock(&inside_mutex);
    }
    pthread_mutex_lock(&total_mutex);
    total++;
    pthread_mutex_unlock(&total_mutex);
  }
  pthread_exit(0);
}
