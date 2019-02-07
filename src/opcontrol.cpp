#include "../include/controllers.hpp"

//drive controller buttons
ControllerButton Btn_flipper(ControllerId::master, ControllerDigital::B); //flip the flipper
ControllerButton Btn_flipperUp(ControllerId::master, ControllerDigital::X); //raise the flipper to the up position
ControllerButton Btn_flipperRam(ControllerId::master, ControllerDigital::Y); //set the flipper to ramming speed
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

void WriteFlywheelSpeed()
{
	//write speed
	partner.setText(0, 0, "Speed: " + std::to_string(Flywheel::speed) + "  ");
}

void opcontrol()
{
	Robot::WriteMessage("Opcontrol started!");
	//start the flipper
	Flipper::StartUp();
	while (true)
	{
		pros::delay(20);

		//flywheel control button checks
		if(Btn_flywheelIncreaseSpeed.changedToPressed())
		{
			//increase speed
			Flywheel::speed += 20;
			WriteFlywheelSpeed();
		}
		else if(Btn_flywheelDecreaseSpeed.changedToPressed())
		{
			//decrease speed
			Flywheel::speed -= 20;
			WriteFlywheelSpeed();
		}
		//check for toggling the intake
		if(Btn_intake.changedToPressed())
		{
			//toggle whether intake is running
			Intake::IsRunning = !Intake::IsRunning;
		}

		//flywheel fine control button checks
		if(Btn_flywheelFineIncreaseSpeed.changedToPressed())
		{
			//increase speed
			Flywheel::speed += 5;
			WriteFlywheelSpeed();
		}
		else if(Btn_flywheelFineDecreaseSpeed.changedToPressed())
		{
			//decrease speed
			Flywheel::speed -= 5;
			WriteFlywheelSpeed();
		}
		//flywheel control button checks
		if(Btn_flywheelHighSpeed.changedToPressed())
		{
			//increase speed
			Flywheel::speed = 170;
			WriteFlywheelSpeed();
		}
		else if(Btn_flywheelLowSpeed.changedToPressed())
		{
			//decrease speed
			Flywheel::speed -= 120;
			WriteFlywheelSpeed();
		}

		//check for a request to flip a cap
		if(Btn_flipper.changedToPressed())
		{
			//request a flip
			Flipper::RequestFlip();
		}
		//raise the flipper to the upper position
		if(Btn_flipperUp.changedToPressed())
		{
			//raise the flipper
			Flipper::Raise();
		}
		//set the flipper to ramming speed
		if(Btn_flipperRam.changedToPressed())
		{
			//ram the flipper
			Flipper::Ramming();
		}
		//toggle direction of intake
		if(Btn_intakeReverse.changedToPressed())
		{
			//toggle the direction of the flipper
			Intake::IsBackwards = !Intake::IsBackwards;
		}

		//run all controller scripts
		//intake run controller
		Intake::Controller();
		//flipper position controller
		Flipper::Controller();
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
