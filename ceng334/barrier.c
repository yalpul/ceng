#include <stdio.h>
#include <pthread.h>

int init(int n);
int barrier_point(void);

pthread_mutex_t _barrier_mutex;
pthread_cond_t _barrier_cond;
int _barrier;

void *run(void*);

int main(int argc, char **argv)
{
  pthread_t tids[4];
  pthread_attr_t attr;
  int params[4] = {100, 200, 300, 400};
  int i;

  pthread_attr_init(&attr);
  init(4);

  for (i = 0; i < 4; i++)
    pthread_create(&tids[i], &attr, run, &params[i]);

  for (i = 0; i < 4; i++)
    pthread_join(tids[i], NULL);

  return 0;
}

int init(int n)
{
  _barrier = n;
  pthread_mutex_init(&_barrier_mutex, NULL);
  pthread_cond_init(&_barrier_cond, NULL);

  return 0;
}

int barrier_point()
{
  pthread_mutex_lock(&_barrier_mutex);
  _barrier--;
  if (_barrier == 0)
    pthread_cond_broadcast(&_barrier_cond);
  else
    pthread_cond_wait(&_barrier_cond, &_barrier_mutex);
  pthread_mutex_unlock(&_barrier_mutex);

  return 0;
}

void *run(void*v)
{
  int arg = *(int*)v;
  int i;
  for (i = 0; i < arg; i++)
    printf("%d\n", i);

  barrier_point();
  for (i = arg; i < arg*2; i++)
    printf("%d\n", i);

  pthread_exit(0);
}
