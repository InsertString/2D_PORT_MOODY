#include "main.h"
#include "robot_includes/pid.h"



PID::PID() {
  kp = 0;
  ki = 0;
  kd = 0;

  target = 0;
  error = 0;
  past_error = 0;
  integral_limit = 0;
  integral = 0;
  derivative = 0;
  time_interval = 20;
  const_integral = false;
}




//set PID constants
//@param value for constant P
//@param value for constant I
//@param value for constant D
void PID::set_Constants(double p, double i, double d) {
  kp = p;
  ki = i;
  kd = d;
}




//sets default values for PID
//@param value for the target of the PID
void PID::set_pid_vars(int targ, int int_limit, int const_integral_val) {
  const_integral = true;
  target = targ;
  const_integral_value = const_integral_val;
  integral_limit = int_limit;
}




//sets default values for PID
//@param value for the target of the PID
void PID::set_pid_vars(int targ, int int_limit) {
  const_integral = false;
  target = targ;
  const_integral_value = 0;
  integral_limit = int_limit;
}



//displays the error to terminal
void PID::display_output() {
  printf("%5d", error);
}



//generates the output for the PID
//@param value for the current value
//@param value for the maximum output
int PID::output(double current, int max_out) {

  //temperary variable for output
  int out;

  //since error has not yet been refreshed, set past_error to equal error
  past_error = error;

  //refresh error
  error = target - current;

  //checks for constant integral
  if (const_integral == false) {
    //check if error is within integral limit
    if (abs(error) < integral_limit)
      //refresh integral
      integral += error;
    else
      //reset integral
      integral = 0;
  }
  else {
    if (error > 0)
      //set positive integral
      integral = const_integral_value;
    else if (error < 0)
      //set negetive integral
      integral = -const_integral_value;
  }

  //set derivative
  derivative = (error - past_error) / time_interval;

  //set the output
  out = (error * kp) + (integral * ki) + (derivative * kd);

  //check if the output is within the maximum
  if (out > max_out) out = max_out;
  else if (out < (-max_out)) out = -max_out;
  else out = out;

  //return the output
  return out;
}
