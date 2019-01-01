#ifndef CONTROLLERS_HPP
#define CONTROLLERS_HPP

#include "main.h"
////////////////////Variable declarations////////////////////

//general variables
#define MOTOR_GEARSET_06_MAXSPEED 100 //maximum speed for the 36:1 gear set
#define MOTOR_GEARSET_18_MAXSPEED 200 //maximum speed for the 18:1 gear set
#define MOTOR_GEARSET_36_MAXSPEED 600 //maximum speed for the 6:1 gear set

//AUTONOMOUS SWITCH
//#define AUTO_FAR
//#define AUTO_RED

//controllers
extern Controller masterController;
//extern Controller partnerController;

//port variables
#define driveLeftForwardPort 1
#define driveLeftBackPort 2
#define driveRightForwardPort 3
#define driveRightBackPort 4
#define flywheelTopPort 14
#define flywheelBottomPort 15
#define armPort 11
#define flippinPort 12
#define intakePort 16
#define intakeLimitPort 'A'
#define visionPort 5

//motors
namespace Motors
{
  //motors
  extern pros::Motor* flywheelTop;
  extern pros::Motor* flywheelBottom;
  extern pros::Motor* arm;
  extern pros::Motor* flippin;
  extern pros::Motor* intake;
}

//flywheel controller
namespace Flywheel
{
  //are we in flywheel speed finding mode?
  //#define FLYWHEEL_FINE_CONTROL_MODE
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
  const int HighSpeeds[] = {100, 170, 142, 133, 145}; //the speeds for the high flag
  const int LowSpeeds[] = {115, 105, 118, 120, 133}; //the speeds for the low flag

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
  extern ChassisControllerIntegrated controller;
}

//arm controller
namespace Arm
{
  //position of arm
  extern int position;

  //arm bounds
  const int LowerBound = -50;
  const int UpperBound = 550;

  //arm heights
  const int PostHeight = 550;

  //arm controller sets the arm to the position
  void Controller();
}

namespace Flippin
{
const int startupFlipAmount = 100;

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
namespace Sensors
{
  extern pros::Vision vision;
}

#endif
