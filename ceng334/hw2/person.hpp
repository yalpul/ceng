#ifndef _PERSON_H
#define _PERSON_H

#include "monitor.h"

struct person: public Monitor {
  int id;
  static int last_id;
  int weight_person;
  int initial_floor;
  int destination_floor;
  // 1 -> high
  // 2 -> low
  int priority;
  bool allowed;
  Condition leave_elevator;
public:
  person();

  enum class action {
    request,
    enter,
    leave
  };

  void place();
  void notify_cabin_come();
  void travel();
  void get_off_elevator();
  void print_person(action a);
  void allow();

};

#endif
