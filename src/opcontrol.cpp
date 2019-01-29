#include "../include/controllers.hpp"

//buttons
ControllerButton Btn_intake(ControllerDigital::A); //toggle the intake
ControllerButton Btn_flywheelIncreaseSpeed(ControllerDigital::R1); //increase the flywheel speed by 5
ControllerButton Btn_flywheelDecreaseSpeed(ControllerDigital::R2); //decrease the flywheel speed by 5
ControllerButton Btn_flywheelFineIncreaseSpeed(ControllerDigital::L1); //increase the flywheel speed by 1
ControllerButton Btn_flywheelFineDecreaseSpeed(ControllerDigital::L2); //decrease the flywheel speed by 1
ControllerButton Btn_flipper(ControllerDigital::B); //flip the flipper
ControllerButton Btn_flipperUp(ControllerDigital::X); //raise the flipper to the up position
ControllerButton Btn_flipperRam(ControllerDigital::Y); //set the flipper to ramming speed
ControllerButton Btn_intakeReverse(ControllerDigital::left); //toggle the direction of the intake

void opcontrol()
{
	//start the flipper
	Flipper::StartUp();
	while (true)
	{
		pros::delay(20);

		//flywheel control button checks
		if(Btn_flywheelIncreaseSpeed.changedToPressed())
		{
			//increase speed
			Flywheel::speed += 5;
			//set speed text
			master->setText(1, 0, "Speed: " + std::to_string(Flywheel::speed) + "   ");
		}
		else if(Btn_flywheelDecreaseSpeed.changedToPressed())
		{
			//decrease speed
			Flywheel::speed -= 5;
			//set speed text
			master->setText(1, 0, "Speed: " + std::to_string(Flywheel::speed) + "   ");
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
			Flywheel::speed += 1;
			//set speed text
			master->setText(1, 0, "Speed: " + std::to_string(Flywheel::speed) + "   ");
		}
		else if(Btn_flywheelFineDecreaseSpeed.changedToPressed())
		{
			//decrease speed
			Flywheel::speed -= 1;
			//set speed text
			master->setText(1, 0, "Speed: " + std::to_string(Flywheel::speed) + "   ");
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
		//flywheel speed controller
		Flywheel::Controller();
		//intake run controller
		Intake::Controller();
		//flipper position controller
		Flipper::Controller();
		//open loop tank control for chassis
		//Chassis::controller.tank(master->getAnalog(ControllerAnalog::leftY), master->getAnalog(ControllerAnalog::rightY));
		//open loop arcade control for chassis
		Chassis::controller.arcade(master->getAnalog(ControllerAnalog::leftY), master->getAnalog(ControllerAnalog::rightX), 0.05);


		//motor test code
		Motor* testMotor = new Motor(10);
		if(master->getDigital(ControllerDigital::up))
		{
			//turn motor on
			testMotor->move(127);
		}
		else if(master->getDigital(ControllerDigital::down))
		{
			//turn motor on backwards
			testMotor->move(-127);
		}
		else
		{
			//stop motor
			testMotor->move(0);
		}
		}
}
