#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main()
{

  int fd = shm_open("test", O_CREAT | O_RDWR, 0666);

  char *ptr = mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  int a;

  scanf("%d", &a);
  puts(ptr);
  return 0;
}
