#include "controller.hpp"


//buttons
okapi::ControllerButton Btn_flywheelMax(okapi::ControllerDigital::X);
okapi::ControllerButton Btn_flywheelStop(okapi::ControllerDigital::B);
okapi::ControllerButton Btn_flywheelVariable(okapi::ControllerDigital::Y);
okapi::ControllerButton Btn_flywheelIncrease(okapi::ControllerDigital::R1);
okapi::ControllerButton Btn_flywheelDecrease(okapi::ControllerDigital::R2);
okapi::ControllerButton Btn_flip(okapi::ControllerDigital::A);
okapi::ControllerButton Btn_armUp(okapi::ControllerDigital::L1);
okapi::ControllerButton Btn_armDown(okapi::ControllerDigital::L2);
okapi::ControllerButton Btn_intake(okapi::ControllerDigital::up);

void opcontrol()
{
	while (true)
	{
		//wait
		pros::delay(20);

		//check for flywheel full speed mode
		if(Btn_flywheelMax.isPressed())
		{
			//set the flywheel to full speed
			Flywheel::mode = Flywheel::Max;
		}
		//check for flywheel stopping mode
		if(Btn_flywheelStop.isPressed())
		{
			//set the flywheel to stopping
			Flywheel::mode = Flywheel::Stopped;
		}
		//check for flywheel variable speed mode
		if(Btn_flywheelVariable.isPressed())
		{
			//set the flywheel to variable mode
			Flywheel::mode = Flywheel::Variable;
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
		else
		{
			//stop intake
			Intake::running = false;
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
