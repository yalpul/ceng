#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define INIT_FLAG -1
#define BACKG 0
#define FOREG 1
#define PREV 2
#define EXIT 3
#define REDIR 4
#define PIPE 5

int tokenize(char *buf, char **argv);
void run(char **argv, int fg);
void to_history(char **argv, char **prev_argv);
void run_redir(char **argv);
void run_pipe(char **argv);

const int MAX_LINE = 80;
int main()
{
  char buf1[MAX_LINE];
  char buf2[MAX_LINE];
  char *next_buf = buf1;
  char *prev_argv[MAX_LINE/2];
  char *argv[MAX_LINE/2];
  int old_fg = INIT_FLAG;

  while (1)
  {
    printf("osh> ");
    fflush(stdout);
    fgets(next_buf, MAX_LINE, stdin);
    int fg = tokenize(next_buf, argv);
    if (fg == PREV)
      run(prev_argv, old_fg);
    else if (fg == EXIT)
      break;
    else if (fg == REDIR)
      run_redir(argv);
    else if (fg == PIPE)
      run_pipe(argv);
    else
    {
      run(argv, fg);
      to_history(argv, prev_argv);
      next_buf = next_buf == buf1 ? buf2 : buf1;
      old_fg = fg;
    }
  }

  return 0;
}

int tokenize(char *buf, char *argv[MAX_LINE/2])
{
  char *p = strtok(buf, " \n");
  int i = 0;
  if (strcmp(p, "!!") == 0)
    return PREV;
  else if (strcmp(p, "exit") == 0)
    return EXIT;
  while (p != NULL)
  {
    argv[i++] = p;
    p = strtok(NULL, " \n");
  }

  if (i > 1)
  {
    if (*argv[i-1] == '&')
    {
      argv[i-1] = NULL;
      return BACKG;
    }
    else if (*argv[i-2] == '>' || *argv[i-2] == '<')
      return REDIR;
    else if (*argv[i-2] == '|')
      return PIPE;
    argv[i] = NULL;
    return FOREG;
  }
  else
  {
    argv[i] = NULL;
    return FOREG;
  }
}

void run(char *argv[MAX_LINE/2], int fg)
{
  pid_t pid;

  if (fg == INIT_FLAG)
  {
    puts("No command in history.");
    return;
  }

  if ((pid = fork()) == 0)
    execvp(argv[0], argv);
  else if (fg)
    wait(NULL);
}

void run_redir(char *argv[MAX_LINE/2])
{
  int i = 0, fd;
  char c;
  pid_t pid;
  c = *argv[i];
  while (c != '<' && c != '>')
  {
    i++;
    c = *argv[i];
  }
  argv[i] = NULL;
  if ((pid = fork()) == 0)
  {
    fd = open(argv[i+1], O_CREAT | O_RDWR, 0666);
    dup2(fd, c == '>' ? STDOUT_FILENO:STDIN_FILENO);
    execvp(argv[0], argv);
  }
  else
  {
    wait(NULL);
  }
}

void run_pipe(char *argv[MAX_LINE/2])
{
  int i = 0, fd[2];
  pid_t pid, pid2;
  while (*argv[i] != '|')
    i++;
  argv[i] = NULL;
  pipe(fd);
  if ((pid = fork()) == 0)
  {
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    execlp(argv[i+1], argv[i+1], NULL);
  }
  else if ((pid2 = fork()) == 0)
  {
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    execvp(argv[0], argv);
  }
  else
  {
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
  }
}

void to_history(char **argv, char **prev_argv)
{
  int i = 0;
  while (argv[i])
  {
    prev_argv[i] = argv[i];
    i++;
  }
  prev_argv[i] = NULL;
}
