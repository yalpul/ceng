#include <stdio.h>
#include <pthread.h>
#define MAX_SIZE 100

int buff1[MAX_SIZE], buff2[MAX_SIZE];

void *sort(void*);
void *merge(void*);
void swap(int*, int*);

int main()
{
  pthread_t sort1_t, sort2_t, merge_t;
  pthread_attr_t attr;
  int count, i, bound1[2], bound2[2];

  pthread_attr_init(&attr);
  scanf("%d", &count);
  for (i = 0; i < count; i++)
    scanf("%d", &buff1[i]);
  bound1[0] = 0;
  bound1[1] = bound2[0] = count/2;
  bound2[1] = count;

  pthread_create(&sort1_t, &attr, sort, bound1);
  pthread_create(&sort2_t, &attr, sort, bound2);
  pthread_join(sort1_t, NULL);
  pthread_join(sort2_t, NULL);
  pthread_create(&merge_t, &attr, merge, &count);
  pthread_join(merge_t, NULL);
  for (i = 0; i < count; i++)
    printf("%d ", buff2[i]);
  puts("");

  return 0;
}

void *sort(void *b)
{
  int *bounds = (int*)b;
  int low = bounds[0], high = bounds[1];
  int i, j, min;

  for (i = low; i < high-1; i++)
  {
    min = i;
    for (j = i+1; j < high; j++)
      if (buff1[j] < buff1[min])
        min = j;
    swap(&buff1[i], &buff1[min]);
  }
  pthread_exit(0);
}

void swap(int *f, int *s)
{
  int tmp = *f;
  *f = *s;
  *s = tmp;
}

void *merge(void *v)
{
  int count = *(int*)v;
  int i = 0, j = count/2;
  int k = 0;

  while (i < count/2 && j < count)
    buff2[k++] = buff1[i] < buff1[j] ? buff1[i++] : buff1[j++];

  while (i < count/2)
    buff2[k++] = buff1[i++];
  while (j < count)
    buff2[k++] = buff1[j++];
  pthread_exit(0);
}
