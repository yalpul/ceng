#include <cstdio>
#include <unistd.h>
#include <algorithm>
#include "elevator.hpp"

elevator::elevator(const elevator_args& args)
  : num_floors(args.num_floors), num_people(args.num_people),
  weight_capacity(args.weight_capacity),
  person_capacity(args.person_capacity), TRAVEL_TIME(args.TRAVEL_TIME),
  IDLE_TIME(args.IDLE_TIME), IN_OUT_TIME(args.IN_OUT_TIME),
  elevator_state(state::idle), current_floor(0), travelled(0),
  carried_weight(0), carried_people(0), started(false), 
  elevator_idle(this), started_cond(this), wait_cond(this)
{
  people_on_floors = new std::vector<person*>[num_floors];
  destination_q = std::vector<bool>(num_floors, false);
  floors_hp = std::vector<Condition>(num_floors, Condition(this));
  floors_lp = std::vector<Condition>(num_floors, Condition(this));
}

elevator::~elevator()
{
  delete[] people_on_floors;
}

void elevator::start_notify()
{
  __synchronized__;
  started = true;
  started_cond.notifyAll();
}

void elevator::start_wait()
{
  __synchronized__;
  if (started)
    return;
  started_cond.wait();
}

bool elevator::place(person *p, int floor)
{
  __synchronized__;
  std::vector<person*>& waiting_people = people_on_floors[floor];
  if (elevator_state == state::idle) {
    if (floor != current_floor) {
      destination_q[floor] = true;
      elevator_state = floor > current_floor ?
        state::moving_up : state::moving_down;
    }
    p->print_person(person::action::request);
    print_elevator();
  }
  else if ((elevator_state == state::moving_up &&
        floor >= current_floor &&
        p->destination_floor > floor) ||
      (elevator_state == state::moving_down &&
       floor <= current_floor &&
       p->destination_floor < floor)) {
    if (floor != current_floor)
      destination_q[floor] = true;
    p->print_person(person::action::request);
    print_elevator();
  }
  else
    return false;
  if (std::find(waiting_people.begin(), waiting_people.end(), p)
      == waiting_people.end())
    waiting_people.push_back(p);
  bool elevator_dir = elevator_state == state::moving_up ? true : false;
  bool person_dir = p->destination_floor - p->initial_floor > 0;
  return elevator_dir == person_dir || elevator_state == state::idle;
}

// Needs to be inside monitor
void elevator::print_elevator()
{
  printf("Elevator (%s, %d, %d, %d -> ",
      elevator_state == state::idle ? "Idle" :
      (elevator_state == state::moving_up ? "Moving-up" : "Moving-down"), 
      carried_weight, carried_people, current_floor);
  // below is destination queue
  int i;
  if (elevator_state == state::moving_down) {
    for (i = current_floor-1; i >= 0; i--)
      if (destination_q[i]) {
        printf("%d", i);
        break;
      }
    while (--i >= 0)
      if (destination_q[i])
        printf(",%d", i);
  }
  else if (elevator_state == state::moving_up) {
    for (i = current_floor+1; i < num_floors; i++)
      if (destination_q[i]) {
        printf("%d", i);
        break;
      }
    while (++i < num_floors)
      if (destination_q[i])
        printf(",%d", i);
  }
  printf("%s\n", ")");
}

void elevator::get_in_cabin(person *p)
{
  __synchronized__;
  std::vector<person*>& waiting_people = people_on_floors[current_floor];
  for (auto it = waiting_people.begin(); it != waiting_people.end(); ++it)
    if (*it == p) {
      waiting_people.erase(it);
      break;
    }
  carried_people++;
  carried_weight += p->weight_person;
  cabin.push_back(p);
  p->print_person(person::action::enter);
  destination_q[p->destination_floor] = true;
  if (elevator_state == state::idle)
    elevator_state = p->destination_floor - p->initial_floor > 0 ?
      state::moving_up : state::moving_down;
  print_elevator();
}

void elevator::become_idle()
{
  elevator_state = state::idle;
  elevator_idle.notifyAll();
}

void elevator::get_off_cabin(person *p)
{
  __synchronized__;
  for (auto it = cabin.begin(); it != cabin.end(); ++it)
    if (*it == p) {
      cabin.erase(it);
      break;
    }
  carried_people--;
  carried_weight -= p->weight_person;
  travelled++;
  p->print_person(person::action::leave);
  print_elevator();
}

bool elevator::has_dest()
{
  __synchronized__;
  for (bool b : destination_q)
    if (b)
      return true;
  return false;
}

bool elevator::has_dest_lockless()
{
  for (bool b : destination_q)
    if (b)
      return true;
  return false;
}

void elevator::run()
{
  __synchronized__;
  while (!finished()) {
    work();
  }
}

void elevator::work()
{
  switch (elevator_state) {
  case state::idle:
    do {
      wait_cond.timedwait(IDLE_TIME);
      if (finished())
        return;
    }
    while (should_wait());
    if (people_on_floors[current_floor].size() > 0) {
      load_cabin();
      notify_people();
      wait_cond.timedwait(IN_OUT_TIME);
    }
    break;
  case state::moving_up:
    if (people_on_floors[current_floor].size() > 0) {
      load_cabin();
      notify_people();
      wait_cond.timedwait(IN_OUT_TIME);
    }
    if (move_up()) {
      unload_cabin();
      if (elevator_state == state::idle)
        break;
      load_cabin();
      notify_people();
      wait_cond.timedwait(IN_OUT_TIME);
    }
    break;
  case state::moving_down:
    if (people_on_floors[current_floor].size() > 0) {
      load_cabin();
      notify_people();
      wait_cond.timedwait(IN_OUT_TIME);
    }
    if (move_down()) {
      unload_cabin();
      if (elevator_state == state::idle)
        break;
      load_cabin();
      notify_people();
      wait_cond.timedwait(IN_OUT_TIME);
    }
    break;
  }
}

bool elevator::should_wait()
{
  return !has_dest_lockless() &&
    people_on_floors[current_floor].size() == 0;
}

void elevator::load_cabin()
{
  int available_person = person_capacity - carried_people;
  int available_weight = weight_capacity - carried_weight;
  if (available_person == 0)
    return;
  for (person *p : people_on_floors[current_floor])
    if (p->priority == 1 && p->weight_person <= available_weight &&
        ((p->destination_floor > current_floor &&
         elevator_state != state::moving_down)
        ||
        (p->destination_floor < current_floor &&
         elevator_state != state::moving_up))) {
      p->allow();
      available_weight -= p->weight_person;
      if (--available_person == 0)
        return;
    }

  for (person *p : people_on_floors[current_floor])
    if (p->priority == 2 && p->weight_person <= available_weight &&
        ((p->destination_floor > current_floor &&
         elevator_state != state::moving_down)
        ||
        (p->destination_floor < current_floor &&
         elevator_state != state::moving_up))) {

      p->allow();
      available_weight -= p->weight_person;
      if (--available_person == 0)
        return;
    }
}

void elevator::notify_people()
{
  floors_hp[current_floor].notifyAll();
  wait_cond.timedwait(IDLE_TIME/2);
  floors_lp[current_floor].notifyAll();
  wait_cond.timedwait(IDLE_TIME/2);
}

void elevator::wait_for_idle()
{
  __synchronized__;
  elevator_idle.wait();
}

bool elevator::move_up()
{
  usleep(TRAVEL_TIME);
  current_floor++;
  bool stop_here = destination_q[current_floor];
  destination_q[current_floor] = false;
  if (!has_dest_lockless())
    become_idle();
  print_elevator();
  return stop_here;
}

bool elevator::move_down()
{
  usleep(TRAVEL_TIME);
  current_floor--;
  bool stop_here = destination_q[current_floor];
  destination_q[current_floor] = false;
  if (!has_dest_lockless())
    become_idle();
  print_elevator();
  return stop_here;
}

void elevator::unload_cabin()
{
  for (person *p : cabin)
    if (p->destination_floor == current_floor)
      p->get_off_elevator();
}

bool elevator::finished()
{
  if (travelled == num_people)
    return true;
  return false;
}

void elevator::wait_cabin_come(int floor, int p)
{
  __synchronized__;
  if (p == 1)
      floors_hp[floor].wait();
  else
      floors_lp[floor].wait();
}
