#pragma once

#include "main.h"

//general variables
#define MOTOR_GEARSET_06_MAXSPEED 600 //maximum speed for the 36:1 gear set
#define MOTOR_GEARSET_18_MAXSPEED 200 //maximum speed for the 18:1 gear set
#define MOTOR_GEARSET_36_MAXSPEED 100 //maximum speed for the 6:1 gear set

//controllers
extern Controller* master;
extern Controller* partner;

namespace Ports
{
  //motor ports
  const int Flywheel = 1;
  const int DriveLeftFront = 2;
  const int DriveLeftBack = 3;
  const int DriveRightFront = 4;
  const int DriveRightBack = 5;
  const int Intake = 6;
  const int Flipper = 7;
  //sensor ports
  const int IntakeSwitch = 'A';
  const int Vision = 20;
}

namespace Motors
{
  //intake
  extern Motor* intake;
  //flipper
  extern Motor* flipper;
}

namespace Flipper
{
  //position variables
  const int startPos = 0;
  const int Raised = 105;
  const int Lowered = 480;
  const int Ram = 270;
  const int MaxSpeed = 200;
  //start the flipper position
  void StartUp();
  //position controller
  void Controller();
  //request the controller to flip
  void RequestFlip();
  //tell the flipper to move to the up position
  void Raise();
  //tell the flipper to move to the ramming position
  void Ramming();
}

namespace Intake
{
  extern bool IsRunning;
  extern bool IsBackwards;

  void Controller();
}

namespace Chassis
{
  //closed and open loop chassis controller using the V5 brain integrated controllers
  extern ChassisControllerIntegrated controller;
}

namespace Flywheel
{
  //velocity PID controller
  extern AsyncVelIntegratedController velController;

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

namespace Sensors
{
  namespace Vision
  {
    //the dreaded sensor incarnate
    extern pros::Vision* vision;

    //prints the area, length, height, and position of the largest object that matches the given signature
    void VisionPrintLargest(pros::vision_signature_s_t sig);
  }
}
