#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CUSTOMERS 5
#define RESOURCES 4

int available[RESOURCES];
int maximum[CUSTOMERS][RESOURCES];
int allocation[CUSTOMERS][RESOURCES];
int need[CUSTOMERS][RESOURCES];

int request_resources(int customer, int *request);
void release_resources(int customer, int *release);
int greater(int *first, int *second);
void allocate(int customer, int *resources);
int is_safe(void);
void print_info(void);

int main(int argc, char **argv)
{
  int i, j;
  char buff[25];
  int buff_res[RESOURCES];
  int customer;
  for (i = 0; i < RESOURCES; i++)
    available[i] = atoi(argv[i+1]);
  for (i = 0; i < CUSTOMERS; i++)
    for (j = 0; j < RESOURCES; j++)
    {
      scanf("%d", &maximum[i][j]);
      need[i][j] = maximum[i][j];
    }
  getchar();
  while (1)
  {
    printf("> ");
    fflush(stdout);
    scanf("%25s", buff);
    if (strncmp(buff, "QUIT", 4) == 0)
      break;
    else if (strncmp(buff, "RQ", 2) == 0)
    {
      // take numbers and request
      scanf("%d", &customer);
      for (i = 0; i < RESOURCES; i++)
        scanf("%d", &buff_res[i]);
      printf("Requesting resources %d %d %d %d for customer %d\n",
          buff_res[0],buff_res[1],buff_res[2],buff_res[3],customer);

      if (request_resources(customer, buff_res))
        puts("Acquired.");
      else
        puts("Request denied.");
    }
    else if (strncmp(buff, "RL", 2) == 0)
    {
      // take numbers and release
      scanf("%d", &customer);
      for (i = 0; i < RESOURCES; i++)
        scanf("%d", &buff_res[i]);
      printf("Releasing resources %d %d %d %d for customer %d\n",
          buff_res[0],buff_res[1],buff_res[2],buff_res[3],customer);

      release_resources(customer, buff_res);
      puts("Released.");
    }
    else if (buff[0] == '*')
      print_info();
    else
      puts("Invalid command");
  }
  puts("Bye.");

  return 0;
}

void allocate(int customer, int *resources)
{
  int i;
  for (i = 0; i < RESOURCES; i++)
  {
    allocation[customer][i] += resources[i];
    need[customer][i] -= resources[i];
    available[i] -= resources[i];
  }
}

void release_resources(int customer, int *release)
{
  int i;
  for (i = 0; i < RESOURCES; i++)
  {
    allocation[customer][i] -= release[i];
    need[customer][i] += release[i];
    available[i] += release[i];
  }
}

int request_resources(int customer, int *request)
{
  if (!greater(available, request))
    return 0;
  allocate(customer, request);
  if (is_safe())
    return 1;
  release_resources(customer, request);
  return 0;
}

int greater(int *first, int *second)
{
  int i;
  for (i = 0; i < RESOURCES; i++)
    if (first[i] < second[i])
      return 0;
  return 1;
}

int is_safe()
{
  int i, j, k;
  int finish[CUSTOMERS] = {0};
  int work[RESOURCES];

  for (i = 0; i < RESOURCES; i++)
    work[i] = available[i];

  for (i = 0; i < CUSTOMERS; i++)
    for (j = 0; j < CUSTOMERS; j++)
      if (!finish[j] && greater(work, need[j]))
      {
        finish[j] = 1;
        for (k = 0; k < RESOURCES; k++)
          work[k] += allocation[j][k];
      }
  for (i = 0; i < CUSTOMERS; i++)
    if (finish[i] == 0)
      return 0;
  return 1;
}

void print_info()
{
  int i, j;
  puts("Available:");
  for (i = 0; i < RESOURCES; i++)
    printf("%d ", available[i]);
  puts("");
  puts("Maximum:");
  for (i = 0; i < CUSTOMERS; i++)
  {
    for (j = 0; j < RESOURCES; j++)
      printf("%d ", maximum[i][j]);
    puts("");
  }
  puts("Allocation:");
  for (i = 0; i < CUSTOMERS; i++)
  {
    for (j = 0; j < RESOURCES; j++)
      printf("%d ", allocation[i][j]);
    puts("");
  }
  puts("Need:");
  for (i = 0; i < CUSTOMERS; i++)
  {
    for (j = 0; j < RESOURCES; j++)
      printf("%d ", need[i][j]);
    puts("");
  }
}
