#include "controller.hpp"

//functions
void UpdateFlywheel()
{
	//set the flywheel to variable mode
	Flywheel::mode = Flywheel::Variable;
	//tell the flywheel to update its speed
	Flywheel::SetSpeed();
	//write the row and flag to the controller screen
	//check flag
	if(Flywheel::isHighFlag)
	{
		masterController.setText(1, 0, "High, " + std::to_string(Flywheel::row) + "   ");
	}
	else
	{
		masterController.setText(1, 0, "Low, " + std::to_string(Flywheel::row) + "   ");
	}
}

//buttons
ControllerButton Btn_postHeight(ControllerDigital::down);
ControllerButton Btn_flip(ControllerDigital::left);
ControllerButton Btn_armUp(ControllerDigital::L1);
ControllerButton Btn_armDown(ControllerDigital::L2);
ControllerButton Btn_intake(ControllerDigital::A);
#ifdef FLYWHEEL_FINE_CONTROL_MODE
ControllerButton Btn_flywheelIncreaseSpeed(ControllerDigital::R1);
ControllerButton Btn_flywheelDecreaseSpeed(ControllerDigital::R2);
#else
ControllerButton Btn_flywheelCoast(ControllerDigital::Y);
ControllerButton Btn_flywheelLowFlag(ControllerDigital::B);
ControllerButton Btn_flywheelHighFlag(ControllerDigital::X);
ControllerButton Btn_flywheelIncreaseRow(ControllerDigital::R1);
ControllerButton Btn_flywheelDecreaseRow(ControllerDigital::R2);
#endif

void opcontrol()
{
	#ifdef FLYWHEEL_FINE_CONTROL_MODE
	//set the flywheel to variable mode
	Flywheel::mode = Flywheel::Variable;
	//set speed to 0
	Flywheel::speed = 0;
	#endif
	while (true)
	{
		//wait
		pros::delay(20);
		#ifdef FLYWHEEL_FINE_CONTROL_MODE
		//set the flywheel to variable mode
		Flywheel::mode = Flywheel::Variable;
		if(Btn_flywheelIncreaseSpeed.changedToPressed())
		{
			//increase speed
			Flywheel::speed += 5;
			//set speed text
			masterController.setText(1, 0, "Speed: " + std::to_string(Flywheel::speed) + "   ");
		}
		else if(Btn_flywheelDecreaseSpeed.changedToPressed())
		{
			//decrease speed
			Flywheel::speed -= 5;
			//set speed text
			masterController.setText(1, 0, "Speed: " + std::to_string(Flywheel::speed) + "   ");
		}
		#else
		//check for high or low flag modes
		if(Btn_flywheelHighFlag.changedToPressed())
		{
			//set the flywheel to high flag mode
			Flywheel::isHighFlag = true;
			//update the flywheel
			UpdateFlywheel();
		}
		else if(Btn_flywheelLowFlag.changedToPressed())
		{
			//set the flywheel to low flag mode
			Flywheel::isHighFlag = false;
			//update the flywheel
			UpdateFlywheel();
		}
		//check for changing rows
		if(Btn_flywheelIncreaseRow.changedToPressed())
		{
			//check if its at the edge of the range
			if(!(Flywheel::row >= 4))
			{
				//increase
				Flywheel::row += 1;
			}
			//update the flywheel
			UpdateFlywheel();
		}
		else if(Btn_flywheelDecreaseRow.changedToPressed())
		{
			//check if its at the edge of the range
			if(!(Flywheel::row <= 0))
			{
				//decrease
				Flywheel::row -= 1;
			}
			//update the flywheel
			UpdateFlywheel();
		}
		//check for flywheel variable speed mode
		if(Btn_flywheelCoast.changedToPressed())
		{
			//check if the flywheel is already set to coasting
			if(Flywheel::speed == 100)
			{
				//stop the flywheel
				Flywheel::mode = Flywheel::Stopped;
				Flywheel::speed = 0;
			}
			else
			{
				//set the speed to 100
				Flywheel::speed = 100;
			}
		}
		#endif
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
		//go to arm heights?
		if (Btn_postHeight.changedToPressed())
		{
			//go to low post height
			Arm::position = Arm::PostHeight;
		}
		// run the intake?
		if(Btn_intake.changedToPressed())
		{
			//check if the intake is running
			if(Intake::running == true)
			{
				//turn off intake
				Intake::running = false;
			}
			else
			{
				//turn on intake
				Intake::running = true;
			}
		}

		//run controllers
		Manager::Manager(); //Check for start-of-game and end-of-game events and perform their functions
		Time::Controller(); //run timestep
		Flywheel::Controller(); //flywheel velocity controller
		Arm::Controller(); //Arm position tracking
		Intake::Controller(); //Run intake until sensor is triggered
		Flippin::Controller(); //Controller position of flipper

		//tank drive controller
		Drive::controller.tank(masterController.getAnalog(okapi::ControllerAnalog::leftY), masterController.getAnalog(okapi::ControllerAnalog::rightY));
	}
}
