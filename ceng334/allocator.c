#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int request(unsigned int amount, char *buf, char method);
void release(char *buf);
void compact(void);
void stat(void);

int request_b(unsigned int amount, char *buf);
int request_w(unsigned int amount, char *buf);
int request_f(unsigned int amount, char *buf);

typedef struct rec_alloc {
  unsigned int amount;
  unsigned int address;
  char proc[8];
  struct rec_alloc *next;
} rec_alloc;

rec_alloc *
mk_rec_alloc(unsigned int amnt, unsigned int addr, char *b, rec_alloc *n);
void deallocate(rec_alloc *rec);

rec_alloc *memory_head = NULL;
unsigned int total;

int main(int argc, char **argv)
{
  char buf[25];
  unsigned int amount;
  char method;
  unsigned char *memory;

  total = atoi(argv[1]);
  printf("Starting with %u bytes of memory.\n", total);

  while (1)
  {
    printf("allocator> ");
    fflush(stdout);
    scanf("%s", buf);
    if (strcmp(buf, "RQ") == 0)
    {
      scanf("%s %u %c", buf, &amount, &method);
      printf("%u memory is allocated for process %s using method %c\n",
          amount, buf, method);
      if (request(amount, buf, method))
        puts("Allocated.");
      else
        puts("Failed.");
    }
    else if (strcmp(buf, "RL") == 0)
    {
      scanf("%s", buf);
      printf("Process %s is deallocated\n", buf);
      release(buf);
    }
    else if (strcmp(buf, "STAT") == 0)
      stat();
    else if (buf[0] == 'C')
      compact();
    else if (buf[0] == 'X')
      break;
    else
      puts("Invalid command.");
  }

  deallocate(memory_head);
  return 0;
}

int request(unsigned int amount, char *buf, char method)
{
  if (memory_head)
    switch (method)
    {
      case 'B':
        return request_b(amount, buf);
      case 'W':
        return request_w(amount, buf);
      case 'F':
        return request_f(amount, buf);
    }
  else
  {
    if (amount > total)
      return 0;
    memory_head = mk_rec_alloc(amount, 0U, buf, NULL);
    return 1;
  }
  return 0;
}

int request_b(unsigned int amount, char *buf)
{
  unsigned int best_surplus = (unsigned) -1;
  unsigned int surplus;
  rec_alloc *rec = memory_head;
  rec_alloc *next = memory_head->next;
  rec_alloc *best = rec;
  if (memory_head->address >= amount)
  {
    best = NULL;
    best_surplus = memory_head->address - amount;
  }
  while (next)
  {
    surplus = next->address - rec->address - rec->amount - amount;
    if (!(surplus >> 31) && surplus < best_surplus)
    {
      best_surplus = surplus;
      best = rec;
    }
    rec = next;
    next = next->next;
  }
  surplus = total - (rec->address+rec->amount+amount);
  if (!(surplus >> 31) && surplus < best_surplus)
  {
    best = rec;
    best_surplus = surplus;
  }
  if (best_surplus == (unsigned) -1)
    return 0;
  if (best)
  {
    rec_alloc *new_rec = 
      mk_rec_alloc(amount, best->address+best->amount, buf, best->next);
    best->next = new_rec;
  }
  else
    memory_head = mk_rec_alloc(amount, 0U, buf, memory_head);
  return 1;
}

int request_f(unsigned int amount, char *buf)
{
  rec_alloc *rec = memory_head;
  rec_alloc *next = memory_head->next;
  if (memory_head->address >= amount)
  {
    memory_head = mk_rec_alloc(amount, 0U, buf, memory_head);
    return 1;
  }
  while (next)
  {
    if (rec->address + rec->amount + amount <= next->address)
    {
      rec->next = mk_rec_alloc(amount, rec->address+rec->amount, buf, next);
      return 1;
    }
    rec = next;
    next = next->next;
  }
  if (rec->address + rec->amount + amount <= total)
  {
    rec->next = mk_rec_alloc(amount, rec->address+rec->amount, buf, NULL);
    return 1;
  }
  else
    return 0;
}

int request_w(unsigned int amount, char *buf)
{
  unsigned int worst_surplus = 0;
  unsigned int surplus;
  rec_alloc *rec = memory_head;
  rec_alloc *next = memory_head->next;
  rec_alloc *worst = rec;
  if (memory_head->address >= amount)
  {
    worst = NULL;
    worst_surplus = memory_head->address - amount;
  }
  while (next)
  {
    surplus = next->address - rec->address - rec->amount - amount;
    if (!(surplus >> 31) && surplus > worst_surplus)
    {
      worst_surplus = surplus;
      worst = rec;
    }
    rec = next;
    next = next->next;
  }
  surplus = total - (rec->address+rec->amount+amount);
  if (!(surplus >> 31) && surplus > worst_surplus)
  {
    worst = rec;
    worst_surplus = surplus;
  }
  if (worst_surplus == 0)
    return 0;
  if (worst)
  {
    rec_alloc *new_rec = 
      mk_rec_alloc(amount, worst->address+worst->amount, buf, worst->next);
    worst->next = new_rec;
  }
  else
    memory_head = mk_rec_alloc(amount, 0U, buf, memory_head);
  return 1;
}

void release(char *buf)
{
  rec_alloc *rec, *next;
  if (!memory_head)
    return;

  rec = memory_head;
  next = memory_head->next;

  if (strcmp(memory_head->proc, buf) == 0)
  {
    rec_alloc *new_head = memory_head->next;
    free(memory_head);
    memory_head = new_head;
    return;
  }

  while (next)
  {
    if (strcmp(next->proc, buf) == 0)
    {
      rec->next = next->next;
      free(next);
      return;
    }
    rec = next;
    next = next->next;
  }
}

void compact()
{
  rec_alloc *rec;
  unsigned int next_addr;
  if (!memory_head)
    return;
  if (memory_head->address)
    memory_head->address = 0U;
  next_addr = memory_head->address+memory_head->amount;
  rec = memory_head->next;
  while (rec)
  {
    rec->address = next_addr;
    next_addr = rec->address+rec->amount;
    rec = rec->next;
  }
}

void stat()
{
  if (memory_head)
  {
    rec_alloc *rec = memory_head;
    if (memory_head->address > 0)
      printf("Addresses[0:%u] Unused\n", rec->address-1);

    while (rec)
    {
      unsigned int upper = rec->address+rec->amount-1;
      rec_alloc *next = rec->next;
      printf("Addresses[%u:%u] %s\n",
          rec->address, upper, rec->proc);
      if (next && next->address != upper+1)
        printf("Addresses[%u:%u] Unused\n",
            upper+1, next->address-1);
      else if (!next && upper+1 < total)
        printf("Addresses[%u:%u] Unused\n",
            upper+1, total-1);
      rec = next;
    }
  }
  else
    printf("Addresses[0:%u] Unused\n", total-1);
}

rec_alloc *
mk_rec_alloc(unsigned int amnt, unsigned int addr, char *b, rec_alloc *n)
{
  rec_alloc *new_node = malloc(sizeof(rec_alloc));
  new_node->amount = amnt;
  new_node->address = addr;
  strcpy(new_node->proc, b);
  new_node->next = n;
  return new_node;
}

void deallocate(rec_alloc *rec)
{
  rec_alloc *next;
  while (rec)
  {
    next = rec->next;
    free(rec);
    rec = next;
  }
}
