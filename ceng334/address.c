#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  uint32_t addr, offset, page;
  
  addr = atoi(argv[1]);
  offset = addr & 0xfff;
  page = addr >> 12;

  printf("The address %u contains:\n", addr);
  printf("page number: %u\n", page);
  printf("offset: %u\n", offset);

  return 0;
}
