#ifndef _ELEVATOR_H
#define _ELEVATOR_H

#include <vector>
#include "monitor.h"
#include "person.hpp"

struct elevator_args {
  int num_floors;
  int num_people;
  int weight_capacity;
  int person_capacity;
  int TRAVEL_TIME;
  int IDLE_TIME;
  int IN_OUT_TIME;
};


class elevator: public Monitor {
  std::vector<person*> *people_on_floors;
  std::vector<person*> cabin;
  std::vector<bool> destination_q;
  std::vector<Condition> floors_hp, floors_lp;
  const int num_floors;
  const int num_people;
  const int weight_capacity;
  const int person_capacity;
  const int TRAVEL_TIME;
  const int IDLE_TIME;
  const int IN_OUT_TIME;
  enum class state {
    idle, moving_up, moving_down
  } elevator_state;

  int current_floor;
  int travelled;
  int carried_weight;
  int carried_people;

  bool started;

  Condition elevator_idle;
  Condition started_cond;
  Condition wait_cond;
public:
  elevator(const elevator_args& args);


  ~elevator();
  bool place(person *p, int floor);
  void get_in_cabin(person *p);
  void get_off_cabin(person *p);
  bool has_dest();
  bool has_dest_lockless();
  bool finished();
  void work();
  bool move_up();
  bool move_down();
  void print_elevator();
  void unload_cabin();
  void load_cabin();
  void wait_for_idle();
  void become_idle();
  void notify_people();
  bool should_wait();
  void start_notify();
  void start_wait();
  void wait_cabin_come(int floor, int priority);
  void run();


};

#endif
