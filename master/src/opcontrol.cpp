#include "../include/controllers.hpp"

//buttons
ControllerButton Btn_flywheelIncreaseSpeed(ControllerDigital::R1);
ControllerButton Btn_flywheelDecreaseSpeed(ControllerDigital::R2);

void opcontrol()
{
	while (true)
	{
		pros::delay(20);
		//flywheel
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
	}
}
