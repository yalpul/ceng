#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void *philopher(void*);
void pickup_forks(int num);
void release_forks(int num);
void test(int num);

enum {THINKING, HUNGRY, EATING} state[5]={THINKING};
pthread_cond_t conds[5];
pthread_mutex_t cond_mutex;

int main()
{
  int i;
  pthread_t philosophers[5];
  pthread_attr_t attr;

  srand(time(NULL));
  pthread_attr_init(&attr);
  pthread_mutex_init(&cond_mutex, NULL);
  for (i = 0; i < 5; i++)
    pthread_cond_init(&conds[i], NULL);

  puts("Threads starting");
  for (i = 0; i < 5; i++)
    pthread_create(&philosophers[i], &attr, philopher, (void*)(long)i);

  for (i = 0; i < 5; i++)
    pthread_join(philosophers[i], NULL);
  puts("Threads finished");

  return 0;
}

void *philopher(void *v)
{
  int phil_id = (int) v;
  int i, time;

  for (i = 0; i < 10; i++)
  {
    printf("Philosopher %d is in turn %d\n", phil_id, i);
    time = rand()%3+1;
    pickup_forks(phil_id);
    sleep(time);
    release_forks(phil_id);
    sleep(time);
  }

  pthread_exit(0);
}

void pickup_forks(int num)
{
  state[num] = HUNGRY;
  test(num);
  pthread_mutex_lock(&cond_mutex);
  if (state[num] != EATING)
    pthread_cond_wait(&conds[num], &cond_mutex);
  pthread_mutex_unlock(&cond_mutex);
}

void release_forks(int num)
{
  state[num] = THINKING;
  test((num+1)%5);
  test((num+4)%5);
}

void test(int num)
{
  pthread_mutex_lock(&cond_mutex);
  if (state[(num+4)%5] != EATING &&
      state[(num+1)%5] != EATING &&
      state[num] == HUNGRY)
  {
    state[num] = EATING;
    pthread_cond_signal(&conds[num]);
  }
  pthread_mutex_unlock(&cond_mutex);
}
