#include <stdio.h>
#include <pthread.h>

int num;
void *primes(void*);
int isprime(int);
int main()
{
  pthread_t tid;
  pthread_attr_t attr;

  pthread_attr_init(&attr);

  scanf("%d", &num);
  pthread_create(&tid, &attr, primes, NULL);
  pthread_join(tid, NULL);
  return 0;
}

void *primes(void *v)
{
  int i;
  puts("2");
  puts("3");
  for (i = 4; i <= num; i++)
    if (isprime(i))
      printf("%d\n", i);
  pthread_exit(0);
}

int isprime(int n)
{
  if (n % 2 == 0)
    return 0;
  if (n % 3 == 0)
    return 0;
  int f = 5;
  while (f*f <= n)
  {
    if (n % f == 0)
      return 0;
    if (n % (f+2) == 0)
      return 0;
    f += 6;
  }
  return 1;
}
