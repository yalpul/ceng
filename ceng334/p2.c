#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
  int fd = shm_open("test", O_CREAT | O_RDWR, 0666);

  ftruncate(fd, 4096);

  char * ptr = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  strcpy(ptr, "denem1234");
  int a;
  scanf("%d", &a);

  return 0;
}
