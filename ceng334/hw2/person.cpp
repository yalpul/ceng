#include <cstdio>
#include "person.hpp"
#include "elevator.hpp"

extern elevator *e;

int person::last_id = 0;

person::person()
  : allowed(false), leave_elevator(this)
{
  id = last_id++;
}

void person::allow()
{
  allowed = true;
}

void person::place()
{
  while (true) {
    if (e->place(this, initial_floor)) {
      e->wait_cabin_come(initial_floor, priority);
      if (allowed)
        break;
      else
        e->wait_for_idle();
    }
    else {
      e->wait_for_idle();
    }
  }
  e->get_in_cabin(this);
}

void person::travel()
{
  __synchronized__;
  leave_elevator.wait();
  e->get_off_cabin(this);
}

// to be used by elevator
void person::get_off_elevator()
{
  __synchronized__;
  leave_elevator.notify();
}

void person::print_person(action a)
{
  printf("Person (%d, %s, %d -> %d, %d) ",
      id, priority == 1 ? "hp" : "lp", initial_floor,
      destination_floor, weight_person);
  switch (a) {
  case action::request:
    printf("%s\n", "made a request");
    break;
  case action::enter:
    printf("%s\n", "entered the elevator");
    break;
  case action::leave:
    printf("%s\n", "has left the elevator");
    break;
  }
}
