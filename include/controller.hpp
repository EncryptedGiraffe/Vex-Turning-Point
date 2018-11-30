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
extern okapi::Controller partnerController;

//port variables
#define driveLeftPort 20
#define driveRightPort 19
#define flywheelTopPort 15
#define flywheelBottomPort 14
#define armTopPort 18
#define armBottomPort 17
#define flippinPort 11
#define intakePort 16
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
    Variable,
    Max
  };

  extern Mode mode;
  extern int speed;

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
  const int LowerBound = 0;
  const int UpperBound = 450;

  //arm controller 0 = stay, 1 = up, -1 = down
  void Simple(int mode);

  //arm controller sets the arm to the position
  void Controller();
}

namespace Flippin
{
  extern void Flip();
}

namespace Intake
{
  extern bool running;

  extern void Controller();
}

#endif
