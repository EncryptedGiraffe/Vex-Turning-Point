#ifndef CONTROLLERS_HPP
#define CONTROLLERS_HPP

#include "main.h"
////////////////////Variable declarations////////////////////

//general variables
#define MOTOR_GEARSET_06_MAXSPEED 100 //maximum speed for the 36:1 gear set
#define MOTOR_GEARSET_18_MAXSPEED 200 //maximum speed for the 18:1 gear set
#define MOTOR_GEARSET_36_MAXSPEED 600 //maximum speed for the 6:1 gear set

//controllers
extern okapi::Controller masterController;
//extern okapi::Controller partnerController;

//port variables
#define driveLeftPort 20
#define driveRightPort 19
#define flywheelTopPort 15
#define flywheelBottomPort 14
#define armTopPort 18
#define armBottomPort 17
#define flippinPort 11
#define intakePort 13
#define intakeLimit 'A'

//motors
namespace Motors
{
  //motors
  extern pros::Motor* flywheelTop;
  extern pros::Motor* flywheelBottom;
  extern pros::Motor* armTop;
  extern pros::Motor* armBottom;
  extern pros::Motor* flippin;
  extern pros::Motor* intake;
}

//flywheel controller
namespace Flywheel
{
  //flywheel speeds
  enum Mode
  {
    Stopped,
    Variable
  };

  //velocity management variables
  extern Mode mode;
  extern int speed;

  //flywheel speeds for different tiles for the high and low ball-toggled flags
  // first element is for tile 1 away from flags, last element full-court
  const int HighSpeeds[] = {100, 105, 140, 140, 170}; //the speeds for the high flag
  const int LowSpeeds[] = {130, 170, 140, 115, 120}; //the speeds for the low flag

  //speeds
  extern int row;
  extern bool isHighFlag;

  //set flywheel speed
  void SetSpeed();

  //manage flywheel speed
  void Controller();
};

//drive controller
namespace Drive
{
  //tank drive
  extern okapi::ChassisControllerIntegrated controller;
}

//arm controller
namespace Arm
{
  //position of arm
  extern int position;

  //arm bounds
  const int LowerBound = -50;
  const int UpperBound = 450;

  //arm heights
  const int LowPostHeight = 300;
  const int HighPostHeight = 450;

  //arm controller sets the arm to the position
  void Controller();
}

namespace Flippin
{
  extern void Flip();

  extern void Controller();
}

namespace Intake
{
  extern bool running;

  extern void Controller();
}

namespace Time
{
  extern int gameTime;

  extern void Controller();
}

namespace Manager
{
  extern bool isStarted;

  extern void Manager();
}

#endif
