#pragma once

#include "main.h"

//general variables
#define MOTOR_GEARSET_06_MAXSPEED 600 //maximum speed for the 36:1 gear set
#define MOTOR_GEARSET_18_MAXSPEED 200 //maximum speed for the 18:1 gear set
#define MOTOR_GEARSET_36_MAXSPEED 100 //maximum speed for the 6:1 gear set

//controllers
extern Controller* master;

namespace Ports
{
  //ports
  const int Flywheel = 1;
  const int DriveLeftFront = 2;
  const int DriveLeftBack = 3;
  const int DriveRightFront = 4;
  const int DriveRightBack = 5;
  const int Vision = 6;
}

namespace Motors
{
  //flywheel
  extern Motor* flywheel;
}

namespace Chassis
{
  //closed and open loop chassis controller using the V5 brain integrated controllers
  extern ChassisControllerIntegrated controller;
}

namespace Flywheel
{
  //are we in flywheel speed finding mode?
  #define FLYWHEEL_FINE_CONTROL_MODE
  #define FLYWHEEL_FINE_CONTROL_INCREMENT 5

  //flywheel speeds
  enum Mode
  {
    Stopped,
    Variable
  };

  //velocity management variables
  extern Mode mode;
  extern int speed;

  //manage flywheel speed
  void Controller();
}

namespace Vision
{
  extern pros::Vision* vision;
}