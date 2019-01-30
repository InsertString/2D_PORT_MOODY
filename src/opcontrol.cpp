#include "main.h"

void opcontrol() {

	while (true) {
		chassis.drive();
		lift.drive();
		ball_system.drive();
		lcd_control();

		pros::delay(20);
	}
}
