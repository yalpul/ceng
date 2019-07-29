#include <stdio.h>
#include <pthread.h>

int table[9][9];

int rows_status, cols_status, subs_status;

void *check_rows(void*);
void *check_cols(void*);
void *check_subs(void*);

int main()
{
  int i, j;
  pthread_t row_t, col_t, sub_t;
  pthread_attr_t attr;

  for (i = 0; i < 9; i++)
    for (j = 0; j < 9; j++)
      scanf("%d", &table[i][j]);

  pthread_attr_init(&attr);
  pthread_create(&row_t, &attr, check_rows, NULL);
  pthread_create(&col_t, &attr, check_cols, NULL);
  pthread_create(&sub_t, &attr, check_subs, NULL);
  pthread_join(row_t, NULL);
  pthread_join(col_t, NULL);
  pthread_join(sub_t, NULL);
  printf("Status: %d\n", rows_status && cols_status && subs_status);
  return 0;
}

void *check_rows(void *v)
{
  unsigned int status;
  int i, j;
  for (i = 0; i < 9; i++)
  {
    status = 0;
    for (j = 0; j < 9;  j++)
      status |= 1 << table[i][j];
    if (status != 0x3fe)
    {
      rows_status = 0;
      pthread_exit(0);
    }
  }
  rows_status = 1;
  pthread_exit(0);
}

void *check_cols(void *v)
{
  unsigned int status;
  int i, j;
  for (i = 0; i < 9; i++)
  {
    status = 0;
    for (j = 0; j < 9;  j++)
      status |= 1 << table[j][i];
    if (status != 0x3fe)
    {
      cols_status = 0;
      pthread_exit(0);
    }
  }
  cols_status = 1;
  pthread_exit(0);
}

void *check_subs(void *v)
{
  int i, j, k, l;
  unsigned int status;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
    {
      status = 0;
      for (k = i*3; k < (i+1)*3; k++)
        for (l = j*3; l < (j+1)*3; l++)
          status |= 1 << table[k][l];
      if (status != 0x3fe)
      {
        subs_status = 0;
        pthread_exit(0);
      }
    }
  subs_status = 1;
  pthread_exit(0);
}
