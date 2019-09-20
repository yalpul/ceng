#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 256
#define TABLE_SIZE 256
#define FRAMES 256
/*
 * XXX This code includes page replacement.
 * Change FRAMES to 128 to enable it.
 * FIFO will be used.
 */

typedef struct {
  unsigned int page;
  unsigned int offset;
} addr;
addr translate(unsigned int va);

int tlb_current = 0;

int in_tlb(unsigned char tlb[][2], unsigned char page);
void add_to_tlb
(unsigned char tlb[][2], unsigned char page, unsigned char frame);

int main(int argc, char **argv)
{
  FILE *fp = fopen(argv[1], "r");
  FILE *bs = fopen("BACKING_STORE.bin", "rb");
  unsigned int address;
  unsigned int pf, tlb_miss, tlb_hit;
  unsigned char page_table[TABLE_SIZE];
  unsigned char valid_bits[TABLE_SIZE] = {0};
  unsigned char tlb[16][2];
  char memory[FRAMES][PAGE_SIZE];
  unsigned char available = 0;
  int full = 0;
  addr ad;

  pf = tlb_miss = tlb_hit = 0;

  while (!feof(fp))
  {
    char byte;
    int frame;;
    fscanf(fp, "%d ", &address);
    ad = translate(address);
    if ((frame = in_tlb(tlb, ad.page)) != -1)
    {
      tlb_hit++;
      byte = memory[frame][ad.offset];
    }
    else if (valid_bits[ad.page])
    {
      tlb_miss++;
      frame = page_table[ad.page];
      byte = memory[frame][ad.offset];
      add_to_tlb(tlb, ad.page, frame);
    }
    else
    {
      pf++;
      fseek(bs, ad.page*PAGE_SIZE, SEEK_SET);
      fread(&memory[available][0], 1, PAGE_SIZE, bs);
      if (full)
        for (int i = 0; i < TABLE_SIZE; i++)
          if (valid_bits[i] && page_table[i] == available)
          {
            valid_bits[i] = 0;
            break;
          }
      page_table[ad.page] = available;
      valid_bits[ad.page] = 1;
      add_to_tlb(tlb, ad.page, available);
      byte = memory[available][ad.offset];
      available = (available + 1) % FRAMES;
      if (available == 0)
        full = 1;
    }
    printf("Virtual address: %u Physical address: %u Value: %d\n",
        address, page_table[ad.page]*256+ad.offset, (int)byte);
  }
  printf("TLB Hit: %u\nTLB Miss: %u\nPage Fault: %u\n",
      tlb_hit, tlb_miss, pf);
  fclose(fp);
  fclose(bs);

  return 0;
}

addr translate(unsigned int va)
{
  addr pa;
  unsigned int offset = va & 0xff;
  unsigned int pagen = va >> 8 & 0xff;
  pa.page = pagen;
  pa.offset = offset;
  return pa;
}

int in_tlb(unsigned char tlb[16][2], unsigned char page)
{
  int i;
  for (i = 0; i < tlb_current; i++)
    if (tlb[i][0] == page)
      return tlb[i][1];
  return -1;
}

void add_to_tlb
(unsigned char tlb[][2], unsigned char page, unsigned char frame)
{
  int i;
  if (tlb_current < 16)
  {
    tlb[tlb_current][0] = page;
    tlb[tlb_current][1] = frame;
    tlb_current++;
  }
  else
  {
    for (i = 1; i < 16; i++)
    {
      tlb[i-1][0] = tlb[i][0];
      tlb[i-1][1] = tlb[i][1];
    }
    tlb[15][0] = page;
    tlb[15][1] = frame;
  }
}
