#include "main.h"
#include "controller.hpp"

//variables
bool flippinNewPress;

void opcontrol()
{
	while (true)
	{
		//wait
		pros::delay(20);

		//check for flywheel full speed mode
		if(masterController->get_digital(pros::E_CONTROLLER_DIGITAL_X))
		{
			//set the flywheel to full speed
			Flywheel::speed = Flywheel::maxSpeed;
		}
		//check for flywheel stopping modes
		if(masterController->get_digital(pros::E_CONTROLLER_DIGITAL_B))
		{
				//set the flywheel to stopping
				Flywheel::speed = 0;
		}
		//do we want to flip the flipper
		if(masterController->get_digital(pros::E_CONTROLLER_DIGITAL_Y))
		{
			if(flippinNewPress)
			{
				//flip
				Flippin::Flip();
				//toggle
				flippinNewPress = false;
			}
		}
		else
		{
				//toggle
				flippinNewPress = true;
		}
		//move the arm?
		if(masterController->get_digital(pros::E_CONTROLLER_DIGITAL_R1))
		{
			//go up
			Arm::Simple(1);
		}
		else if(masterController->get_digital(pros::E_CONTROLLER_DIGITAL_R2))
		{
			//go Down
			Arm::Simple(-1);
		}
		else
		{
			//stay still
			Arm::Simple(0);
		}

		//set drive
		Drive::Tank(masterController->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),masterController->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));

		//run all controllers
		Flywheel::Controller();
		Flippin::Controller();
	}
}
