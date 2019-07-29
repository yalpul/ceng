#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
  pid_t pid;
  int fd_r[2];
  int fd_w[2];
  char buf[512];
  int i, len;

  pipe(fd_r);
  pipe(fd_w);

  if ((pid = fork()) == 0)
  {
    close(fd_r[0]);
    close(fd_w[1]);
    read(fd_w[0], buf, 512);
    len = strlen(buf);
    for (i = 0; i < 512 && i < len; i++)
    {
      int b = (int) buf[i];
      if (isupper(b))
        buf[i] = tolower(b);
      else
        buf[i] = toupper(b);
    }
    write(fd_r[1], buf, len);
  }
  else
  {
    close(fd_r[1]);
    close(fd_w[0]);
    write(fd_w[1], argv[1], strlen(argv[1])+1);
    read(fd_r[0], buf, 512);
    printf("%s\n", buf);
    wait(NULL);
  }
  return 0;

}
