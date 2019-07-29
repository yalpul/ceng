#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
  pid_t pid;
  int fd[2];
  char buf[512];
  int file, nbyte;

  pipe(fd);

  if ((pid = fork()) == 0)
  {
    close(fd[1]);
    file = open(argv[2], O_CREAT | O_WRONLY, 0666);
    
    while (1)
    {
      nbyte = read(fd[0], buf, 512);
      if (nbyte == 0)
        break;

      write(file, buf, nbyte);
    }
    close(file);
  }
  else
  {
    close(fd[0]);
    file = open(argv[1], O_RDONLY);

    while (1)
    {
      int nbyte = read(file, buf, 512);
       if (nbyte == 0)
         break;
       write(fd[1], buf, nbyte);
    }
    close(file);
  }
  return 0;
}
