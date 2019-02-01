#include "robot_includes/pid.h"


#ifndef _ROBOT_CLASSES_H_
#define _ROBOT_CLASSES_H_


#define CAT_TARGET 1590
#define CAT_THRESHOLD 1525

#define CAT_INTAKE_IN 1
#define CAT_INTAKE_OUT 2


enum Auto_Function {
  COMPLETE,
  INCOMPLETE,
  FLAGGED
};

enum Cat_Positions {
  LOAD,
  IDLE,
  FIRE
};


class Chassis {
public:
  Chassis();
  void setLeftPower(int power);
  void setRightPower(int power);

  void reset_drive_sensors(bool reset_gyro);
  Auto_Function PID_drive(int target, int max_power);
  Auto_Function PID_turn(int target, int max_power);

  int right_pos();
  int left_pos();

  void drive();
  int drive_step;
  int turn_step;
  void reset_chassis_auto_vars();
private:
  int direction;
  PID drive_pid;
  PID turn_pid;
  int gyro_error;

};


class Lift_Systems {
public:
  Lift_Systems();
  void setFlipperPower(int power);
  void setCBarPower(int power);
  PID CBar_pid;
  int button_pressed();

  void drive();

  int curr_system;
private:
  int flipper_state;
  int cBar_state;
};


class Ball_System {
public:
  Ball_System();
  void setIntakePower(int power);

  void setCatpower(int power);

  Auto_Function shoot();
  Auto_Function intake_ball(int direction);

  int shoot_step;

  void drive();
private:
  Cat_Positions target;
  int Cat_target;
};

#endif
