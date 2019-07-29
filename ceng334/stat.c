#include <stdio.h>
#include <pthread.h>
#define MAX_SIZE 20

double avg;
int min, max;
int count;
int nums[MAX_SIZE];

void *avg_r(void*);
void *min_r(void*);
void *max_r(void*);

int main()
{
  pthread_t avg_t, min_t, max_t;
  pthread_attr_t attr;
  int i;

  pthread_attr_init(&attr);
  scanf("%d", &count);
  for (i = 0; i < count; i++)
    scanf("%d", &nums[i]);

  pthread_create(&avg_t, &attr, avg_r, NULL);
  pthread_create(&min_t, &attr, min_r, NULL);
  pthread_create(&max_t, &attr, max_r, NULL);

  pthread_join(avg_t, NULL);
  pthread_join(min_t, NULL);
  pthread_join(max_t, NULL);

  printf("Avg: %.2f\n", avg);
  printf("Min: %d\n", min);
  printf("Max: %d\n", max);

  return 0;
}

void *avg_r(void *v)
{
  double sum = 0.0;
  int i;
  for (i = 0; i < count; i++)
    sum += nums[i];

  avg = sum / count;
  pthread_exit(0);
}

void *min_r(void *v)
{
  int i;
  min = nums[0];
  for (i = 1; i < count; i++)
    if (nums[i] < min)
      min = nums[i];
  pthread_exit(0);
}

void *max_r(void *v)
{
  int i;
  max = nums[0];
  for (i = 1; i < count; i++)
    if (nums[i] > max)
      max = nums[i];
  pthread_exit(0);
}
