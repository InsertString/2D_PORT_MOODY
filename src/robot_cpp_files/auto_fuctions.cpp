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





void partner_auto(int colour) {
  switch (auto_step) {
    case 0 :
    ball_system.setIntakePower(127);
    lift.setFlipperPower(3);
    i = chassis.PID_drive(3000, 100);
    if (i == COMPLETE || getTime(AUTO_STEP_TIMEOUT) > 2000) {
      advance_auto_step();
    }
    break;
    case 1 :
    cBar.move_absolute(-900, 150);
    advance_auto_step();
    break;
    case 2 :
    int a;
    a = colour == RED ? 900 : -900;
    i = chassis.PID_turn(a, 100);
    if (i == COMPLETE) {
      advance_auto_step();
    }
    break;
    case 3 :
    cBar.move_absolute(-420, 200);
    f = chassis.PID_drive(-500, 70);
    if (f == COMPLETE) {
      i = ball_system.shoot();
      if (i == COMPLETE) {
        advance_auto_step();
      }
    }
    break;
    case 4 :
    advance_auto_step();
    break;
    case 5 :
    i = chassis.PID_drive(3000, 100);
    break;
  }
}





void flag_auto(int colour) {
  switch (auto_step) {
    case 0 :
    ball_system.setIntakePower(127);
    lift.setFlipperPower(3);
    int bbbbb;
    bbbbb = colour == RED ? 1050 : 1150;
    i = chassis.PID_drive(1150, 100);
    if (i == COMPLETE || getTime(AUTO_STEP_TIMEOUT) > 2000) {
      advance_auto_step();
    }
    break;
    case 1 :
    flipper.move_absolute(-300, 100);
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
    i = chassis.PID_drive(-1070, 50);
    if (i == COMPLETE) {
      advance_auto_step();
    }
    break;
    case 4 :
    int tttt;
    tttt = colour == RED ? 680 : -680;
    i = chassis.PID_turn(tttt, 70);//BLUE TURN AMOUNT
    cBar.move_absolute(-900, 150);
    if (i == COMPLETE && cBar.get_position() < -800) {
      advance_auto_step();
    }
    break;
    case 5 :
    i = chassis.PID_drive(-850, 60);
    if (i == COMPLETE) {
      advance_auto_step();
    }
    break;
    case 6 :
    if (getTime(AUTO_STEP_TIMEOUT) > 500) {
      i = ball_system.shoot();
      cBar.move_absolute(-420, 200);
      if (i == COMPLETE) {
        advance_auto_step();
      }
    }
    break;
    case 7 :
    i = chassis.PID_drive(-2000, 100);
    if (i == COMPLETE) {
      advance_auto_step();
    }
    break;
    case 8 :
    tttt = colour == RED ? -540 : 540;
    flipper.move_absolute(-100, 200);
    i = chassis.PID_turn(tttt, 100);
    if (i == COMPLETE) {
      advance_auto_step();
    }
    break;
    case 9 :
    i = chassis.PID_drive(650, 100);
    if (i == COMPLETE) {
      advance_auto_step();
    }
    break;
    case 10 :
    flipper.move_absolute(-350, 200);
    if (flipper.get_position() < -200) {
      i = chassis.PID_drive(-400, 100);
      if (i == COMPLETE) {
        advance_auto_step();
      }
    }
    break;
    case 11 :
    i = chassis.PID_drive(400, 100);
    if (i == COMPLETE) {
      flipper.move_absolute(0, 100);
      if (flipper.get_position() > -10) {
        advance_auto_step();
      }
    }
    break;
    case 12 :
    tttt = colour == RED ? -470 : 470;
    i = chassis.PID_turn(tttt, 100);
    if (i == COMPLETE) {
      advance_auto_step();
    }
    break;
    case 13 :
    i = chassis.PID_drive(2500, 100);
    if (i == COMPLETE) {
      advance_auto_step();
    }
    break;
    case 14 :
    tttt = colour == RED ? 1100 : -1100;
    i = chassis.PID_turn(tttt, 100);
    if (i == COMPLETE) {
      advance_auto_step();
    }
    break;
    case 15 :
    ball_system.shoot();
    chassis.PID_drive(-300, 80);
    break;
  }
}
