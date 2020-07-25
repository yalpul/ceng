#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/wait.h>

#include "message.h"
#include "logging.h"

#define PIPE(fd) socketpair(AF_UNIX, SOCK_STREAM, PF_UNIX, fd)
#define MIN(a,b) ((a) < (b) ? (a) : (b))

char **mk_bidder_args(int num);
int (*spawn_children(int num_bidders))[2];
void handle_bidder(int fd);
struct pollfd *prepare_poll(int (*sockets)[2], int num);
sm handle_cli_connect(cm *c_msg, int i);
sm handle_cli_bid(cm *c_msg);
void send_server_finish(int (*sockets)[2]);

static int BIDDER_MIN_DELAY = -1;
static int START_BID, MIN_INCR, CURRENT_BID,  num_bidders;
static int FINISHED_BIDDERS = 0;
static int WINNER;

static int *PID_TABLE;
static int *BIDDER_STATUS;
struct pollfd *FDS;

int main(int argc, char **argv)
{
  int (*sockets)[2], i;
  scanf("%d %d %d", &START_BID, &MIN_INCR, &num_bidders);
  PID_TABLE = malloc(num_bidders * sizeof(int));
  BIDDER_STATUS = malloc(num_bidders * sizeof(int));
  sockets = spawn_children(num_bidders);
  FDS = prepare_poll(sockets, num_bidders);

  while (FINISHED_BIDDERS < num_bidders && poll(FDS, num_bidders, BIDDER_MIN_DELAY))
    for (i = 0; i < num_bidders; i++)
      if (FDS[i].revents & POLLRDNORM)
        handle_bidder(i);

  print_server_finished(WINNER, CURRENT_BID);
  send_server_finish(sockets);

  for (i = 0; i < num_bidders; i++) {
    int status;
    waitpid(PID_TABLE[i], &status, 0);
    print_client_finished(i, status, status == BIDDER_STATUS[i]);
  }

  for (i = 0; i < num_bidders; i++)
    close(sockets[i][0]);

  free(PID_TABLE);
  free(BIDDER_STATUS);
  free(sockets);
  free(FDS);

  return 0;
}

void send_server_finish(int (*sockets)[2])
{
  sm s_msg = {0};
  oi s_io;
  s_msg.message_id = SERVER_AUCTION_FINISHED;
  s_msg.params.winner_info.winner_id = WINNER;
  s_msg.params.winner_info.winning_bid = CURRENT_BID;
  s_io.type = SERVER_AUCTION_FINISHED;
  s_io.info = s_msg.params;
  for (int i = 0; i < num_bidders; i++) {
    s_io.pid = PID_TABLE[i];
    print_output(&s_io , i);
    write(sockets[i][0], &s_msg, sizeof(sm));
  }
}

struct pollfd *prepare_poll(int (*sockets)[2], int num_bidders)
{
  struct pollfd *FDS = malloc(num_bidders * sizeof(struct pollfd));
  for (int i = 0; i < num_bidders; i++) {
    FDS[i].fd = sockets[i][0];
    FDS[i].events = POLLRDNORM;
  }
  return FDS;
}

void handle_bidder(int i)
{
  cm c_msg;
  sm s_msg = {0};
  ii c_io;
  oi s_io;
  read(FDS[i].fd, &c_msg, sizeof(cm));
  c_io.type = c_msg.message_id;
  c_io.pid = PID_TABLE[i];
  c_io.info = c_msg.params;
  print_input(&c_io, i);
  switch (c_msg.message_id) {
  case CLIENT_CONNECT:
    s_msg = handle_cli_connect(&c_msg, i);
    break;
  case CLIENT_BID:
    s_msg = handle_cli_bid(&c_msg);
    if (s_msg.params.result_info.result == BID_ACCEPTED)
        WINNER = i;
    break;
  case CLIENT_FINISHED:
    FINISHED_BIDDERS++;
    BIDDER_STATUS[i] = c_msg.params.status;
    return;
  default:
    fprintf(stderr,
      "Erroneous client message code: %d\n", c_msg.message_id);
    exit(1);
  }
  s_io.type = s_msg.message_id;
  s_io.pid = PID_TABLE[i];
  s_io.info = s_msg.params;
  print_output(&s_io, i);
  write(FDS[i].fd, &s_msg, sizeof(sm));
}

sm handle_cli_connect(cm *c_msg, int i)
{
  sm s_msg;
  BIDDER_MIN_DELAY = MIN(c_msg->params.delay, BIDDER_MIN_DELAY);
  s_msg.message_id = SERVER_CONNECTION_ESTABLISHED;
  s_msg.params.start_info.client_id = i;
  s_msg.params.start_info.starting_bid = START_BID;
  s_msg.params.start_info.current_bid = CURRENT_BID;
  s_msg.params.start_info.minimum_increment = MIN_INCR;
  return s_msg;
}

sm handle_cli_bid(cm *c_msg)
{
  sm s_msg;
  int bid = c_msg->params.bid;
  s_msg.message_id = SERVER_BID_RESULT;
  if (bid < START_BID)
    s_msg.params.result_info.result = BID_LOWER_THAN_STARTING_BID;
  else if (bid < CURRENT_BID)
    s_msg.params.result_info.result = BID_LOWER_THAN_CURRENT;
  else if ((bid - CURRENT_BID) < MIN_INCR)
    s_msg.params.result_info.result = BID_INCREMENT_LOWER_THAN_MINIMUM;
  else {
    s_msg.params.result_info.result = BID_ACCEPTED;
    CURRENT_BID = bid;
  }
  s_msg.params.result_info.current_bid = CURRENT_BID;
  return s_msg;
}

int (*spawn_children(int num_bidders))[2]
{
  int (*sockets)[2];
  int i, j;
  sockets = malloc(num_bidders * sizeof(int[2]));
  for (i = 0; i < num_bidders; i++) {
    char bidder_path[32];
    int num_bidder_args;
    scanf("%s %d", bidder_path, &num_bidder_args);
    char **bidder_args = mk_bidder_args(num_bidder_args);
    bidder_args[0] = bidder_path;
    PIPE(sockets[i]);
    if ((PID_TABLE[i] = fork())) {
      close(sockets[i][1]);
      for (j = 1; j <= num_bidder_args; j++)
        free(bidder_args[j]);
      free(bidder_args);
    }
    else {
      close(sockets[i][0]);
      dup2(sockets[i][1], 0);
      dup2(sockets[i][1], 1);
      execv(bidder_path, bidder_args);
    }
  }
  return sockets;
}

char **mk_bidder_args(int num)
{
  int i;
  char **args;
  args = malloc(sizeof(char*)*(num+2));
  args[num+1] = NULL;
  for (i = 1; i <= num; i++) {
    args[i] = malloc(32);
    scanf("%32s", args[i]);
  }
  return args;
}
