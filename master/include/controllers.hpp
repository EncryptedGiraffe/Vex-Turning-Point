#pragma once

#include "main.h"

//general variables
#define MOTOR_GEARSET_06_MAXSPEED 600 //maximum speed for the 36:1 gear set
#define MOTOR_GEARSET_18_MAXSPEED 200 //maximum speed for the 18:1 gear set
#define MOTOR_GEARSET_36_MAXSPEED 100 //maximum speed for the 6:1 gear set

//controllers
extern Controller* master;

namespace Motors
{
  //ports
  const int PortFlywheel = 1;

  //flywheel
  extern Motor* flywheel;
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
