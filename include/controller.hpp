#ifndef CONTROLLERS_HPP
#define CONTROLLERS_HPP
#include "main.h"
////////////////////Variable declarations////////////////////

//general variables
#define MOTOR_GEARSET_06_MAXSPEED 100 //maximum speed for the 36:1 gear set
#define MOTOR_GEARSET_18_MAXSPEED 200 //maximum speed for the 18:1 gear set
#define MOTOR_GEARSET_36_MAXSPEED 600 //maximum speed for the 6:1 gear set

//controllers
extern pros::Controller* masterController;
extern pros::Controller* partnerController;

//motors
namespace Motors
{
  extern pros::Motor* driveLeft; //Drive Chassis left motor into Smart Port 2
  extern pros::Motor* driveRight; //Drive Chassis right motor into Smart Port 3
  extern pros::Motor* flywheelTop; //Flywheel top motor into Smart Port 4
  extern pros::Motor* flywheelBottom; //Flywheel bottom motor into Smart Port 5
}

//flywheel controller
namespace Flywheel
{
  //max speed for the flywheel
  extern const int maxSpeed;
  //speed
  extern int speed;
};
////////////////////Function declarations////////////////////

//flywheel controller
void FlywheelController();

#endif
