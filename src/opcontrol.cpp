#include "../include/controllers.hpp"

//drive controller buttons
ControllerButton Btn_flipper(ControllerId::master, ControllerDigital::B); //flip the flipper
//ControllerButton Btn_flipperUp(ControllerId::master, ControllerDigital::X); //raise the flipper to the up position
//ControllerButton Btn_flipperRam(ControllerId::master, ControllerDigital::Y); //set the flipper to ramming speed
ControllerButton Btn_vision(ControllerId::master, ControllerDigital::right); //get the data on the largest object the vision sensor sees
//flywheel controller buttons
ControllerButton Btn_intakeReverse(ControllerId::partner, ControllerDigital::X); //toggle the direction of the intake
ControllerButton Btn_intake(ControllerId::partner, ControllerDigital::A); //toggle the intake
ControllerButton Btn_flywheelIncreaseSpeed(ControllerId::partner, ControllerDigital::R1); //increase the flywheel speed by 5
ControllerButton Btn_flywheelDecreaseSpeed(ControllerId::partner, ControllerDigital::R2); //decrease the flywheel speed by 5
ControllerButton Btn_flywheelFineIncreaseSpeed(ControllerId::partner, ControllerDigital::L1); //increase the flywheel speed by 1
ControllerButton Btn_flywheelFineDecreaseSpeed(ControllerId::partner, ControllerDigital::L2); //decrease the flywheel speed by 1
ControllerButton Btn_flywheelHighSpeed(ControllerId::partner, ControllerDigital::up); //increase the flywheel speed by 20
ControllerButton Btn_flywheelLowSpeed(ControllerId::partner, ControllerDigital::down); //decrease the flywheel speed by 20

void WriteControllerStatus()
{
	//write flywheel speed
	std::string status;
	/*
	status.append("V:");
	status.append(std::to_string(Flywheel::speed));
	status.append(",In:");
	if(Intake::IsRunning)
	{
		status.append("On");
	}
	else
	{
		status.append("Off");
	}
	status.append(",");
	if(Intake::IsBackwards)
	{
		status.append("B");
	}
	else
	{
		status.append("F");
	}
	status.append(" ");
	*/
	/* Character Map
	Intake on/off state. F=forward,B=backward,O=off
	-
	Intake ball state. B=ball,E=empty
	|
	Flywheel high/low state. H=high,L=low
	+/- Flywheel power from current state in increments of 5
	+/- Flywheel power from current state in increments of 5
	+/- Flywheel power from current state in increments of 5
	+/- Flywheel power from current state in increments of 5
	+/- Flywheel power from current state in increments of 5


	Flywheel speed
	Flywheel speed
	Flywheel speed
	*/
	//intake state - character 1
	if(Intake::IsRunning)
	{
		status.append("G");
	}
	else
	{
		status.append("S");
	}
	//intake direction - character 2
	if(Intake::IsBackwards)
	{
		status.append("B");
	}
	else
	{
		status.append("F");
	}
	//separator - character 3
	status.append("-");
	//intake ball info - character 4
	if(Intake::IsBall)
	{
		status.append("B");
	}
	else
	{
		status.append("E");
	}
	//separator - character 5
	status.append("|");
	//flywheel state - character 6
	if(Flywheel::highSpeed)
	{
		status.append("H");
	}
	else
	{
		status.append("L");
	}
	//flywheel speed deviation - characters 7-12
	if(Flywheel::highSpeed)
	{
		//get the deviance
		int d = (Flywheel::speed - Flywheel::HIGH_SPEED) / 5;
		//loop for all 6 characters
		for(int i = 0; i < 6; ++i)
		{
			//check on which side the deviance lies
			if(d > 0)
			{
				//add a plus
				status.append("+");
				//adjust d
				d -= 1;
			}
			else if(d < 0)
			{
				//add a minus
				status.append("-");
				//adjust d
				d += 1;
			}
			else
			{
				//add a space
				status.append(" ");
			}
		}
	}
	else
	{
		//get the deviance
		int d = (Flywheel::speed - Flywheel::LOW_SPEED) / 5;
		//loop for all 6 characters
		for(int i = 0; i < 6; ++i)
		{
			//check on which side the deviance lies
			if(d > 0)
			{
				//add a plus
				status.append("+");
				//adjust d
				d -= 1;
			}
			else if(d < 0)
			{
				//add a minus
				status.append("-");
				//adjust d
				d += 1;
			}
			else
			{
				//add a space
				status.append(" ");
			}
		}
	}
	//flywheel speed - characters 13-15
	//check if the flywheel speed is only two digits
	if(Flywheel::speed < 100)
	{
		//add a zero
		status.append("0");
	}
	status.append(std::to_string(Flywheel::speed));

	//set texts
	partner.setText(0, 0, status);
}

void opcontrol()
{
	Robot::WriteMessage("Opcontrol started!");
	WriteControllerStatus();
	//start the flipper
	//Flipper::StartUp();
	//make sure flywheel is in variable shooting mode
	Flywheel::mode = Flywheel::Variable;
	while (true)
	{
		pros::delay(20);

		//flywheel control button checks
		if(Btn_flywheelIncreaseSpeed.changedToPressed())
		{
			//increase speed
			Flywheel::speed += 20;
			WriteControllerStatus();
		}
		else if(Btn_flywheelDecreaseSpeed.changedToPressed())
		{
			//decrease speed
			Flywheel::speed -= 20;
			WriteControllerStatus();
		}
		//check for toggling the intake
		if(Btn_intake.changedToPressed())
		{
			//toggle whether intake is running
			Intake::IsRunning = !Intake::IsRunning;
			WriteControllerStatus();
		}

		//flywheel fine control button checks
		if(Btn_flywheelFineIncreaseSpeed.changedToPressed())
		{
			//increase speed
			Flywheel::speed += 5;
			WriteControllerStatus();
		}
		else if(Btn_flywheelFineDecreaseSpeed.changedToPressed())
		{
			//decrease speed
			Flywheel::speed -= 5;
			WriteControllerStatus();
		}
		//flywheel control button checks
		if(Btn_flywheelHighSpeed.changedToPressed())
		{
			//increase speed
			Flywheel::speed = Flywheel::HIGH_SPEED;
			WriteControllerStatus();
			Flywheel::highSpeed = true;
		}
		else if(Btn_flywheelLowSpeed.changedToPressed())
		{
			//decrease speed
			Flywheel::speed = Flywheel::LOW_SPEED;
			WriteControllerStatus();
			Flywheel::highSpeed = false;
		}

		//check for flipper activation
		if(Btn_flipper.isPressed())
		{
			//turn on the flipper
			Flipper::flipper.set_value(true);
		}
			else
			{
			//turn off the pper
			Flipper::flipper.set_value(false);
		}
		/*
		Flipper::flipperet_value(true);
		if(Btn_flipper.changedToPressed())
		{
			//request a flip
			Flipper::RequestFlip();
		}
		//raise the flipper to the upper position
		{
		//check for a request to flip a cap
			//raise the flipper
			Flipper::Raise();
		}
		if(Btn_flipperUp.changedToPressed())
		if(Btn_flipperRam.changedToPressed())
		{
			//ram the flipper
			Flipper::Ramming();
		}
		*/
		//toggle direction of intake
		//set the flipper to ramming speed
		if(Btn_intakeReverse.changedToPressed())
		{
			//toggle the direction of the flipper
			Intake::IsBackwards = !Intake::IsBackwards;
			WriteControllerStatus();
		}

		//run all controller scripts
		//intake run controller
		Intake::Controller();
		//flipper position controller
		//Flipper::Controller();
		//open loop tank control for chassis
		//Chassis::controller.tank(master->getAnalog(ControllerAnalog::leftY), master->getAnalog(ControllerAnalog::rightY));
		//open loop arcade control for chassis
		Chassis::controller.arcade(master.getAnalog(ControllerAnalog::leftY), master.getAnalog(ControllerAnalog::rightX), 0.05);
		//flywheel speed controller
		Flywheel::Controller();
		//robot timing system
		Robot::Timer();
		}
}
