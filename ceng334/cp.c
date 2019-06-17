#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
  int first_file = openat(AT_FDCWD, argv[1], O_RDONLY);
  int second_file = openat(AT_FDCWD, argv[2], O_CREAT | O_WRONLY | O_TRUNC);
  struct stat s;

  stat(argv[1], &s);
  unsigned int file_size = (unsigned int) s.st_size;

  char buf[file_size];
  read(first_file, buf, file_size);
  write(second_file, buf, file_size);

  close(first_file);
  close(second_file);
  return 0;
}
