#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void str_gen(unsigned char *buf, int n);
int fifo(int frames, unsigned char* buf, int n);
int lru(int frames, unsigned char* buf, int n);
int opt(int frames, unsigned char* buf, int n);

int main(int argc, char **argv)
{
  int frames = atoi(argv[1]);
  int n = atoi(argv[2]);
  int fifo_pf, lru_pf, opt_pf;
  unsigned char ref_str[n];

  srand(time(NULL));
  str_gen(ref_str, n);
  for (int i = 0; i < n; i++)
    printf("%d ", ref_str[i]);
  puts("");
  fifo_pf = fifo(frames, ref_str, n);
  lru_pf = lru(frames, ref_str, n);
  opt_pf = opt(frames, ref_str, n);
  printf("FIFO: %d\n", fifo_pf);
  printf("LRU: %d\n", lru_pf);
  printf("OPT: %d\n", opt_pf);

  return 0;
}

void str_gen(unsigned char *buf, int n)
{
  int i;
  for (i = 0; i < n; i++)
  {
    unsigned char num = (unsigned char) rand() % 10;
    buf[i] = num;
  }
}

int fifo(int frames, unsigned char *buf, int n)
{
  int pf = 0;
  unsigned char memory[frames];
  int i, current = 0;
  for (i = 0; i < n; i++)
  {
    int j;
    int flag = 0;
    for (j = 0; j < current; j++)
      if (memory[j] == buf[i])
      {
        flag = 1;
        break;
      }
    if (flag)
      continue;
    if (current < frames)
      memory[current++] = buf[i];
    else
    {
      for (j = 1; j < frames; j++)
        memory[j-1] = memory[j];
      memory[frames-1] = buf[i];
    }
    pf++;
  }
  return pf;
}

int lru(int frames, unsigned char *buf, int n)
{
  int pf = 0;
  unsigned char memory[frames];
  int i, current = 0;
  for (i = 0; i < n; i++)
  {
    int j;
    int flag = 0;
    for (j = 0; j < current; j++)
      if (memory[j] == buf[i])
      {
        int k;
        for (k = j+1; k < current; k++)
          memory[k-1] = memory[k];
        memory[current-1] = buf[i];
        flag = 1;
        break;
      }
    if (flag)
      continue;
    if (current < frames)
      memory[current++] = buf[i];
    else
    {
      for (j = 1; j < frames; j++)
        memory[j-1] = memory[j];
      memory[frames-1] = buf[i];
    }
    pf++;
  }
  return pf;
}

int opt(int frames, unsigned char *buf, int n)
{
  int pf = 0;
  unsigned char memory[frames];
  int i, current = 0;
  for (i = 0; i < n; i++)
  {
    int j;
    int flag = 0;
    for (j = 0; j < current; j++)
      if (memory[j] == buf[i])
      {
        flag = 1;
        break;
      }
    if (flag)
      continue;
    if (current < frames)
      memory[current++] = buf[i];
    else
    {
      int k, max=0, max_i=0, flag2;
      for (j = 0; j < current; j++)
      {
        for (k = i+1; k < n; k++)
          if (buf[k] == memory[j])
          {
            if (k > max)
            {
              max = k;
              max_i = j;
            }
            break;
          }
        if (k == n)
        {
          max = k;
          max_i = j;
          break;
        }
      }
      memory[max_i] = buf[i];
    }
    pf++;
  }
  return pf;
}
