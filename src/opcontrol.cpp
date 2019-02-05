#include "../include/controllers.hpp"

//buttons, master controller
ControllerButton Btn_intake(ControllerId::master, ControllerDigital::A); //toggle the intake
ControllerButton Btn_flipper(ControllerId::master, ControllerDigital::B); //flip the flipper
ControllerButton Btn_flipperUp(ControllerId::master, ControllerDigital::X); //raise the flipper to the up position
ControllerButton Btn_flipperRam(ControllerId::master, ControllerDigital::Y); //set the flipper to ramming speed
ControllerButton Btn_intakeReverse(ControllerId::master, ControllerDigital::left); //toggle the direction of the intake
//buttons, partner controller
ControllerButton Btn_flywheelIncreaseSpeed(ControllerId::partner, ControllerDigital::R1); //increase the flywheel speed by 5
ControllerButton Btn_flywheelDecreaseSpeed(ControllerId::partner, ControllerDigital::R2); //decrease the flywheel speed by 5
ControllerButton Btn_flywheelFineIncreaseSpeed(ControllerId::partner, ControllerDigital::L1); //increase the flywheel speed by 1
ControllerButton Btn_flywheelFineDecreaseSpeed(ControllerId::partner, ControllerDigital::L2); //decrease the flywheel speed by 1
ControllerButton Btn_startTargeting(ControllerId::partner, ControllerDigital::A); //start automatic flag targeting
ControllerButton Btn_stopTargeting(ControllerId::partner, ControllerDigital::B); //stop automatic flag targeting

void opcontrol()
{
	Robot::WriteMessage("Opcontrol started!");
	//start the flipper
	Flipper::StartUp();
	//init vision
	Sensors::Vision::Initialize();
	while (true)
	{
		pros::delay(20);

		//check for enable or disable auto targeting
		if(Btn_startTargeting.changedToPressed())
		{
			//start targeting
			Sensors::Vision::StartTargeting();
		}
		if(Btn_stopTargeting.changedToPressed())
		{
			//stop targeting
			Sensors::Vision::StopTargeting();
		}
		//flywheel control button checks
		if(Btn_flywheelIncreaseSpeed.changedToPressed())
		{
			//increase speed
			Flywheel::speed += FLYWHEEL_FINE_CONTROL_INCREMENT;
			//set speed text
			partner.setText(1, 0, "Speed: " + std::to_string(Flywheel::speed) + "   ");
		}
		else if(Btn_flywheelDecreaseSpeed.changedToPressed())
		{
			//decrease speed
			Flywheel::speed -= FLYWHEEL_FINE_CONTROL_INCREMENT;
			//set speed text
			partner.setText(1, 0, "Speed: " + std::to_string(Flywheel::speed) + "   ");
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
			partner.setText(1, 0, "Speed: " + std::to_string(Flywheel::speed) + "   ");
		}
		else if(Btn_flywheelFineDecreaseSpeed.changedToPressed())
		{
			//decrease speed
			Flywheel::speed -= 1;
			//set speed text
			partner.setText(1, 0, "Speed: " + std::to_string(Flywheel::speed) + "   ");
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
		//Targeting controller
		Sensors::Vision::TargetingController();
		//flywheel speed controller
		Sensors::Vision::FlywheelController();
		//flywheel speed controller
		Flywheel::Controller();

		//motor test code
		Motor testMotor = Motor(10);
		if(master.getDigital(ControllerDigital::up))
		{
			//turn motor on
			testMotor.move(127);
		}
		else if(master.getDigital(ControllerDigital::down))
		{
			//turn motor on backwards
			testMotor.move(-127);
		}
		else
		{
			//stop motor
			testMotor.move(0);
		}
		}
}
