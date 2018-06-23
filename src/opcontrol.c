#include "main.h"

//variables
int flywheelMode = 0;

void operatorControl()
{
	while (1)

	{
		//wait
		delay(20);

		//flywheel inputs
		if(joystickGetDigital(1, 7, JOY_UP))
		{
			//full power
			flywheelMode = 1;
		}
		else if(joystickGetDigital(1, 7, JOY_RIGHT))
		{
			//half power
			flywheelMode = 2;
		}
		else if (joystickGetDigital(1, 7, JOY_DOWN))
		{
			//stop
			flywheelMode = 0;
		}
		else if(joystickGetDigital(1, 7, JOY_LEFT))
		{
			//stop quickly
			flywheelMode = -1;
		}
		//get flywheel rps and print it and a newline
		printf((char*)"RPS: ");
		printf("%f\n", FlywheelRPS());
		//flywheel control
		FlywheelDriver(flywheelMode);

		//arm inputs
		if(joystickGetDigital(1, 6, JOY_UP))
		{
			//go up
			ArmDriver(1);
		}
		else if(joystickGetDigital(1, 6, JOY_DOWN))
		{
			//go down
			ArmDriver(-1);
		}
		else
		{
			//stop
			ArmDriver(0);
		}
	}
}
