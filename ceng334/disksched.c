#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CYLINDER 5000
#define RANDOM_SEQUENCE 1000

int fcfs(int init_pos, int *sequence, int length);
int scan(int init_pos, int *sequence, int length);
int cscan(int init_pos, int *sequence, int length);

int comp(const void*, const void*);

int main(int argc, char **argv)
{
  int i;
  int init_pos;
  int sequence[RANDOM_SEQUENCE];
  int fcfs_move, scan_move, cscan_move;
  if (argc != 2)
  {
    puts("Initial position must be given as argument");
    exit(1);
  }
  init_pos = atoi(argv[1]);
  if (init_pos < 0 || init_pos >= MAX_CYLINDER)
  {
    puts("Invalid initial position");
    exit(1);
  }

  srand(time(NULL));
  for (i = 0; i < RANDOM_SEQUENCE; i++)
    sequence[i] = rand() % MAX_CYLINDER;

  fcfs_move = fcfs(init_pos, sequence, RANDOM_SEQUENCE);
  qsort(sequence, RANDOM_SEQUENCE, sizeof(int), comp);
  scan_move = scan(init_pos, sequence, RANDOM_SEQUENCE);
  cscan_move = cscan(init_pos, sequence, RANDOM_SEQUENCE);
  printf("FCFS: %d\nSCAN: %d\nCSCAN: %d\n",
      fcfs_move, scan_move, cscan_move);
  return 0;
}

int fcfs(int init_pos, int *sequence, int length)
{
  int i, current = init_pos, total_distance = 0;
  for (i = 0; i < length; i++)
  {
    int distance = abs(current - sequence[i]);
    current = sequence[i];
    total_distance += distance;
  }
  return total_distance;
}

int scan(int init_pos, int *sequence, int length)
{
  int current = 0, other_direction, total_distance = 0;
  while (init_pos > sequence[current])
    current++;
  other_direction = current;
  total_distance += sequence[current] - init_pos;
  while (current < length-1)
  {
    int distance = sequence[current+1]-sequence[current];
    total_distance += distance;
    current++;
  }
  if (other_direction == 0)
    return total_distance;
  total_distance += sequence[current] - sequence[other_direction-1];
  current = other_direction-1;
  while (current > 0)
  {
    int distance = sequence[current] - sequence[current-1];
    total_distance += distance;
    current--;
  }
  return total_distance;
}

int cscan(int init_pos, int *sequence, int length)
{
  int current = 0, other_direction, total_distance = 0;
  while (init_pos > sequence[current])
    current++;
  other_direction = current;
  total_distance += sequence[current] - init_pos;
  while (current < length-1)
  {
    int distance = sequence[current+1]-sequence[current];
    total_distance += distance;
    current++;
  }
  if (other_direction == 0)
    return total_distance;
  total_distance += sequence[current] - sequence[0];
  current = 0;
  while (current < other_direction-1)
  {
    int distance = sequence[current+1] - sequence[current];
    total_distance += distance;
    current++;
  }
  return total_distance;
}

int comp(const void *left, const void *right)
{
  int left_val = *(int*)left;
  int right_val = *(int*)right;
  if (left_val < right_val)
    return -1;
  else if (left_val == right_val)
    return 0;
  else
    return 1;
}
