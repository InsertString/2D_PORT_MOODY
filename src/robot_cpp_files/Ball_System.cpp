#include "main.h"
#include "robot_includes/robot_classes.h"




Ball_System::Ball_System() {
  target = IDLE;
  Cat_target = 1590;
  shoot_step = 0;
  pull_back_step = 0;
}




void Ball_System::setIntakePower(int power) {
  intake = power;
}



void Ball_System::setCatpower(int power) {
  cat = -power;
}




int intake_state;

Auto_Function Ball_System::shoot() {
  Auto_Function return_state = INCOMPLETE;

  switch (shoot_step) {
    case 0 :
    if (cat_pot.get_value() > 1200) {
      setCatpower(127);
    }
    else {
      setCatpower(0);
      shoot_step++;
    }
    break;
    case 1 :
    if (cat_pot.get_value() < 1485) {
      setCatpower(127);
    }
    else {
      setCatpower(0);
      shoot_step++;
    }
    break;
    case 2 :
    return_state = COMPLETE;
    break;
  }

  return return_state;
}




int a = 1;
int b = 1;
void Ball_System::drive() {



  //CATAPULT
  int power = (Cat_target - cat_pot.get_value()) * 1;

  if (master.get_digital_new_press(DIGITAL_R1)) {
    a = 0;
  }

  if (a == 1) {
    if (cat_pot.get_value() < 1525 && b == 1) {
      setCatpower(power);
    }
    else {
      setCatpower(0);
      b = 0;
      a = 1;
    }
  }
  else if (a == 0) {
    if (cat_pot.get_value() > 700) {
      setCatpower(127);
    }
    else {
      a = 1;
      b = 1;
    }
  }


  //INTAKE
  if (master.get_digital_new_press(DIGITAL_L1)) {
    intake_state = 1;
  }
  else if (master.get_digital(DIGITAL_L2)) {
    intake_state = 2;
  }
  else if ((intake_state != 1 && !master.get_digital(DIGITAL_L2)) || (master.get_digital(DIGITAL_R2))) {
    intake_state = 0;
  }



  if (intake_state == 1 && cat_pot.get_value() > 1200) {
    if (master.get_digital(DIGITAL_L1)) {
      setIntakePower(127);
    }
    else if (light.get_value() > 2500 && light2.get_value() > 2500) {
      setIntakePower(127);
    }
    else if (light.get_value() < 2500 && light2.get_value() < 2500) {
      setIntakePower(0);
    }
  }
  else if (intake_state == 2) {
    setIntakePower(-127);
  }
  else if (intake_state == 0) {
    setIntakePower(0);
  }
  else {
    setIntakePower(0);
  }

}
