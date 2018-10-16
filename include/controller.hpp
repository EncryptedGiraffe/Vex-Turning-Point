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
  //port variables
  extern const int driveLeftPort;
  extern const int driveRightPort;
  extern const int flywheelTopPort;
  extern const int flywheelBottomPort;
  extern const int armTopPort;
  extern const int armBottomPort;
  extern const int flippinPort;
  extern const int intakePort;

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
  //max speed for the flywheel
  extern const int maxSpeed;
  //speed
  extern int speed;

  //flywheel controller
  void Controller();
};

//drive controller
namespace Drive
{
  //tank drive
  extern void Tank(int leftSpeed, int rightSpeed);
}

//arm controller
namespace Arm
{
  //positions for arm
  enum Positions
  {
    Down = 0,
    Middle = 50,
    Up = 100
  };
  //position of arm
  extern int position;

  //arm controller 0 = stay, 1 = up, -1 = down
  void Simple(int mode);
}

namespace Flippin
{
    extern bool flipped;

    extern void Flip();
}

namespace Intake
{
  //simple controller for the intake, 1 = forwards, 0 = stopped, -1 = backwards
  extern void Simple(int mode);
}

#endif
