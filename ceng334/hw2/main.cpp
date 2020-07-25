#include <iostream>
#include <fstream>
#include <vector>
#include <pthread.h>

#include "monitor.h"
#include "elevator.hpp"
#include "person.hpp"

elevator *e;

elevator_args read_elevator_args(std::ifstream& ifs)
{
  elevator_args ea;
  ifs >> ea.num_floors >> ea.num_people >>
    ea.weight_capacity >> ea.person_capacity >> ea.TRAVEL_TIME >>
    ea.IDLE_TIME >> ea.IN_OUT_TIME;
  return ea;
}

std::vector<person> read_person(std::ifstream& ifs, int num)
{
  std::vector<person> pav(num);
  for (int i = 0; i < num; i++)
    ifs >> pav[i].weight_person >> pav[i].initial_floor >>
      pav[i].destination_floor >> pav[i].priority;
  return pav;
}

void *begin_person(void *args)
{
  person *p = static_cast<person*>(args);
  e->start_wait();
  p->place();
  p->travel();

  pthread_exit(NULL);
}

void *begin_elevator(void *v)
{
  e->start_notify();
  e->run();

  pthread_exit(NULL);
}

int main(int argc, char **argv)
{
  if (argc != 2) {
    std::cerr << "Argument error, filename needed" << std::endl;
    return 1;
  }
  std::ifstream ifs(argv[1]);
  elevator_args args = read_elevator_args(ifs);
  e = new elevator(args);
  std::vector<person> pav = read_person(ifs, args.num_people);
  pthread_t *pts = new pthread_t[args.num_people];
  pthread_t elv;


  pthread_create(&elv, NULL, begin_elevator, NULL);

  for (int i = 0; i < args.num_people; i++)
    pthread_create(&pts[i], NULL, begin_person, &pav[i]);
  for (int i = 0; i < args.num_people; i++)
    pthread_join(pts[i], NULL);
  pthread_join(elv, NULL);
  delete e;
  delete[] pts;
}
