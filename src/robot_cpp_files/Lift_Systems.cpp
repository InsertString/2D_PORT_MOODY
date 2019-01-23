#include "main.h"
#include "robot_includes/robot_includes.h"

#define CHAINBAR 1
#define FLIPPER 2
#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4
#define NONE 0

#define SCORING -1850
#define LIFTING -4150
#define GRABBING -300

Lift_Systems::Lift_Systems() {
  curr_system = FLIPPER;
  flipper_state = UP;
}


void Lift_Systems::setFlipperPower(int power) {
  flipper = power;
}


void Lift_Systems::setCBarPower(int power) {
  cBar = power;
}



int Lift_Systems::button_pressed() {
  int rv = NONE;
  if (master.get_digital(DIGITAL_UP)) {
    rv = UP;
  }
  else if (master.get_digital(DIGITAL_LEFT)) {
    rv = LEFT;
  }
  else if (master.get_digital(DIGITAL_DOWN)) {
    rv = DOWN;
  }
  else if (master.get_digital(DIGITAL_RIGHT)) {
    rv = RIGHT;
  }
  return rv;
}



void Lift_Systems::drive() {
  if (master.get_digital_new_press(DIGITAL_R2)) {
    if (flipper_state == UP) flipper_state = DOWN;
    else if (flipper_state == DOWN) flipper_state = UP;
  }

  if (flipper_state == UP) {
    flipper.move_absolute(GRABBING, 200);
  }
  else if (flipper_state == DOWN) {
    flipper.move_absolute(0, 200);
  }
}
