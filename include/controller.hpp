#ifndef CONTROLLERS_HPP
#define CONTROLLERS_HPP
#include "main.h"
////////////////////Variable declarations////////////////////

//general variables
#define MOTOR_GEARSET_06_MAXSPEED 100 //maximum speed for the 36:1 gear set
#define MOTOR_GEARSET_18_MAXSPEED 200 //maximum speed for the 18:1 gear set
#define MOTOR_GEARSET_36_MAXSPEED 600 //maximum speed for the 6:1 gear set

//controllers
extern okapi::Controller* masterController;
extern okapi::Controller* partnerController;

//motors
namespace Motors
{
  //port variables
  extern const int driveLeftPort;
  extern const int driveRightPort;
  extern const int flywheelTopPort;
  extern const int flywheelBottomPort;

  //motors
  extern pros::Motor* driveLeft;
  extern pros::Motor* driveRight;
  extern pros::Motor* flywheelTop;
  extern pros::Motor* flywheelBottom;
}

//flywheel controller
namespace Flywheel
{
  //max speed for the flywheel
  extern const int maxSpeed;
  //speed
  extern int speed;
};

//drive controller
namespace Drive
{
  //DriveController
  extern okapi::ChassisControllerIntegrated driveController;
}

////////////////////Function declarations////////////////////

//flywheel controller
void FlywheelController();

//drive controller
void DriveController();

#endif
