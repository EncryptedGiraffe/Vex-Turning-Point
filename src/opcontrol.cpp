#include "../include/controllers.hpp"

//buttons
ControllerButton Btn_flywheelIncreaseSpeed(ControllerDigital::R1);
ControllerButton Btn_flywheelDecreaseSpeed(ControllerDigital::R2);
ControllerButton Btn_intake(ControllerDigital::A);

void opcontrol()
{
	while (true)
	{
		pros::delay(20);
		//flywheel fine control button checks
		if(Btn_flywheelIncreaseSpeed.changedToPressed())
		{
			//increase speed
			Flywheel::speed += FLYWHEEL_FINE_CONTROL_INCREMENT;
			//set speed text
			master->setText(1, 0, "Speed: " + std::to_string(Flywheel::speed) + "   ");
		}
		else if(Btn_flywheelDecreaseSpeed.changedToPressed())
		{
			//decrease speed
			Flywheel::speed -= FLYWHEEL_FINE_CONTROL_INCREMENT;
			//set speed text
			master->setText(1, 0, "Speed: " + std::to_string(Flywheel::speed) + "   ");
		}
		//check for toggling the intake
		if(Btn_intake.changedToPressed())
		{
			//toggle whether intake is running
			Intake::IsRunning = !Intake::IsRunning;
		}

		//run all controller scripts
		//flywheel speed controller
		Flywheel::Controller();
		//intake run controller
		Intake::Controller();
		//open loop tank control for chassis
		Chassis::controller.tank(master->getAnalog(ControllerAnalog::leftY), master->getAnalog(ControllerAnalog::rightY));
		//open loop arcade control for chassis
		//Chassis::controller.arcade(master->getAnalog(ControllerAnalog::leftY), master->getAnalog(ControllerAnalog::rightX), 0.05);
		}
}
