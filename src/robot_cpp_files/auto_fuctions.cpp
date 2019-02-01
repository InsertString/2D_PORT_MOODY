#include "main.h"
#include "robot_includes/robot_includes.h"




int auto_step;

Auto_Function i;
Auto_Function f;
Auto_Function c;




void start_auto() {
  reset_auto_variables();
  auto_step = 0;
}




void reset_auto_variables() {
  chassis.reset_chassis_auto_vars();
  ball_system.shoot_step = 0;
  resetTimer(AUTO_STEP_TIMEOUT);
}





void advance_auto_step() {
  auto_step++;
  reset_auto_variables();
  resetTimer(AUTO_STEP_TIMEOUT);
  i = f = c = INCOMPLETE;
}





void flag_auto(int colour) {
  switch (auto_step) {
    case 0 :
    ball_system.setIntakePower(127);
    lift.setFlipperPower(3);
    i = chassis.PID_drive(1100, 100);
    if (i == COMPLETE || getTime(AUTO_STEP_TIMEOUT) > 2000) {
      advance_auto_step();
    }
    break;
    case 1 :
    flipper.move_absolute(-250, 150);
    if (flipper.get_position() < -100) {
      i = chassis.PID_drive(-300, 100);
    }
    if (i == COMPLETE || getTime(AUTO_STEP_TIMEOUT) > 2000) {
      advance_auto_step();
    }
    break;
    case 2 :
    i = chassis.PID_drive(300, 100);
    if (i == COMPLETE) {
      advance_auto_step();
    }
    break;
    case 3 :
    i = chassis.PID_drive(-1200, 100);
    if (i == COMPLETE) {
      advance_auto_step();
    }
    break;
    case 4 :
    i = chassis.PID_turn(-720, 100);//BLUE TURN AMOUNT
    cBar.move_absolute(-420, 150);
    if (i == COMPLETE && cBar.get_position() < 300) {
      advance_auto_step();
    }
    break;
    case 5 :
    i = chassis.PID_drive(-500, 100);
    if (i == COMPLETE) {
      advance_auto_step();
    }
    break;
    case 6 :
    i = ball_system.shoot();
    break;
  }
}
