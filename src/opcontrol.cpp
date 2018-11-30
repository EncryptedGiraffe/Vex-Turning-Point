#include "controller.hpp"


//buttons
okapi::ControllerButton Btn_flywheelCoast(okapi::ControllerDigital::Y);
okapi::ControllerButton Btn_lowFlag(okapi::ControllerDigital::B);
okapi::ControllerButton Btn_highFlag(okapi::ControllerDigital::X);
okapi::ControllerButton Btn_increaseRow(okapi::ControllerDigital::R2);
okapi::ControllerButton Btn_decreaseRow(okapi::ControllerDigital::R1);
okapi::ControllerButton Btn_highPost(okapi::ControllerDigital::up);
okapi::ControllerButton Btn_lowPost(okapi::ControllerDigital::down);
okapi::ControllerButton Btn_flip(okapi::ControllerDigital::left);
okapi::ControllerButton Btn_armUp(okapi::ControllerDigital::L1);
okapi::ControllerButton Btn_armDown(okapi::ControllerDigital::L2);
okapi::ControllerButton Btn_intake(okapi::ControllerDigital::A);

void opcontrol()
{
	while (true)
	{
		//wait
		pros::delay(20);

		//check for flywheel stopping mode
		if(Btn_flywheelStop.isPressed())
		{
			//set the flywheel to stopping
			Flywheel::mode = Flywheel::Stopped;
		}
		//check for flywheel variable speed mode
		if(Btn_flywheelCoast.changedToPressed())
		{
			//check if the flywheel is already set to coasting
			if(Flywheel::speed == 100)
			{
				//stop the flywheel
				Flywheel::mode = Flywheel::Stopped;
			}
			else
			{
				//set the flywheel to variable mode
				Flywheel::mode = Flywheel::Variable;
				//set the speed to 100
				Flywheel::speed = 100;
			}
		}
		//do we want to increase flywheel speed
		if(Btn_flywheelIncrease.changedToPressed())
		{
			//increase speed
			Flywheel::speed += 10;
		}
		//do we want to decrease flywheel speed
		if(Btn_flywheelDecrease.changedToPressed())
		{
			//decrease speed
			Flywheel::speed -= 10;
		}
		//do we want to flip the flipper
		if(Btn_flip.changedToPressed())
		{
			//flip
			Flippin::Flip();
		}
		//move the arm?
		if(Btn_armUp.isPressed())
		{
			//increase position
			Arm::position += 10;
		}
		else if(Btn_armDown.isPressed())
		{
			//decrease position
			Arm::position -= 10;
		}
		if(Btn_intake.isPressed())
		{
			//run intake
			Intake::running = true;
		}

		//run controllers
		Flywheel::Controller();
		Arm::Controller();
		Intake::Controller();
		Time::Controller();
		Flippin::Controller();

		//tank drive controller
		Drive::controller.tank(masterController.getAnalog(okapi::ControllerAnalog::leftY), -masterController.getAnalog(okapi::ControllerAnalog::rightY));
	}
}
