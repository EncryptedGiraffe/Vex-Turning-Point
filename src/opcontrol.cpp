#include "controller.hpp"

//variables
bool flippinNewPress = true;
bool flywheelIncreaseNewPress = true;
bool flywheelDecreaseNewPress = true;

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
			Flywheel::speed = Flywheel::Max;
		}
		//check for flywheel stopping mode
		if(masterController->get_digital(pros::E_CONTROLLER_DIGITAL_B))
		{
			//set the flywheel to stopping
			Flywheel::speed = Flywheel::Stopped;
		}
		//check for flywheel variable speed mode
		if(masterController->get_digital(pros::E_CONTROLLER_DIGITAL_Y))
		{
			//set the flywheel to variable mode
			Flywheel::speed = Flywheel::Variable;
		}
		//do we want to increase flywheel speed
		if(masterController->get_digital(pros::E_CONTROLLER_DIGITAL_R1))
		{
			if(flywheelIncreaseNewPress)
			{
				//increase speed
				Flywheel::variableSpeed += 10;
				//set toggle
				flywheelIncreaseNewPress = false;
			}
		}
		else
		{
			//set toggle
			flywheelIncreaseNewPress = true;
		}
		//do we want to decrease flywheel speed
		if(masterController->get_digital(pros::E_CONTROLLER_DIGITAL_R2))
		{
			if(flywheelDecreaseNewPress)
			{
				//decrease speed
				Flywheel::variableSpeed -= 10;
				//set toggle
				flywheelDecreaseNewPress = false;
			}
		}
		else
		{
			//set toggle
			flywheelDecreaseNewPress = true;
		}
		//do we want to flip the flipper
		if(masterController->get_digital(pros::E_CONTROLLER_DIGITAL_A))
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
		if(masterController->get_digital(pros::E_CONTROLLER_DIGITAL_L1))
		{
			//increase position
			Arm::position += 10;
			pros::lcd::set_text(2, std::to_string(Arm::position));
		}
		else if(masterController->get_digital(pros::E_CONTROLLER_DIGITAL_L2))
		{
			//decrease position
			Arm::position -= 10;
			pros::lcd::set_text(2, std::to_string(Arm::position));
		}
		/*
		//arm test code
		if(masterController->get_digital(pros::E_CONTROLLER_DIGITAL_L1))
		{
			Arm::Simple(1);
		}
		else if(masterController->get_digital(pros::E_CONTROLLER_DIGITAL_L2))
		{
			Arm::Simple(-1);
		}
		else
		{
			Arm::Simple(0);
		}
		*/
		//set drive
		Drive::Tank(masterController->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),masterController->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));

		//run controllers
		Flywheel::Controller();
		Arm::Controller();
	}
}
