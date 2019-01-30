#include "main.h"

void opcontrol() {

	while (true) {
		chassis.drive();
		lift.drive();
		ball_system.drive();
		lcd_control();

		if (master.get_digital(DIGITAL_X)) {
			cBar.move_absolute(1200, 200);
		}
		else if (master.get_digital(DIGITAL_A)) {
			cBar.move_absolute(0, 100);
		}
		else if (master.get_digital(DIGITAL_B)) {
			cBar.move_absolute(-790, 200);
		}
		else {
			cBar = 0;
		}

		pros::delay(20);
	}
}
