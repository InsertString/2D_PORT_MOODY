#include "main.h"
//#include "robot_includes/timing.h"

//20 start time slots
int start_time[20];

//restets the start time
//@param timer slot
void resetTimer(int timer_slot) {
  start_time[timer_slot] = pros::millis();
}

//gets the time since last timer reset
//@param timer slot
int getTime(int timer_slot) {
  int i;
  i = pros::millis() - start_time[timer_slot];
  return i;
}

//resets the start time of all timer slots
void resetAllTimers() {
  for (int i = 0; i < 21; i++) {
    resetTimer(i);
  }
}
