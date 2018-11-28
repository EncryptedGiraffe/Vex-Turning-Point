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
  #define driveLeftPort 2
  #define driveRightPort 3
  #define flywheelTopPort 4
  #define flywheelBottomPort 5
  #define armTopPort 6
  #define armBottomPort 7
  #define flippinPort 8
  #define intakePort 9

  //motors
  extern pros::Motor* driveLeft;
  extern pros::Motor* driveRight;
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
  enum Speeds
  {
    Stopped,
    Variable,
    Max
  };

  extern Speeds speed;
  extern int variableSpeed;

  //manage flywheel speed
  void Controller();
};

//drive controller
namespace Drive
{
  //tank drive
  extern void Tank(int leftSpeed, int rightSpeed);
  extern void Arcade(int speed, int rotate);
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
  //simple controller for the intake, 1 = forwards, 0 = stopped, -1 = backwards
  extern void Simple(int mode);
}

#endif
