#pragma once

#include "main.h"

//general variables
#define MOTOR_GEARSET_06_MAXSPEED 600 //maximum speed for the 36:1 gear set
#define MOTOR_GEARSET_18_MAXSPEED 200 //maximum speed for the 18:1 gear set
#define MOTOR_GEARSET_36_MAXSPEED 100 //maximum speed for the 6:1 gear set

//controllers
extern Controller master;
extern Controller partner;

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

namespace Robot
{
  //write a lvgl message to the Brain.
  void WriteMessage(std::string message);
  //declarations
  enum Team_e_t //what team are we on this match?
  {
    Red = 0,
    Blue = 1
  };
  enum StartingTile_e_t //which starting tile do we start on? (Measured from flags)
  {
    Close,
    Far
  };
  //game information
  extern Team_e_t team;
  extern StartingTile_e_t startingTile;
  extern uint32_t flagSig;
  extern bool IsCompetition;
}

namespace Motors
{
  //intake
  extern Motor intake;
  //flipper
  extern Motor flipper;
}

namespace Flipper
{
  //position variables
  const int startPos = 0;
  const int Raised = 35;
  const int Lowered = 160;
  const int Ram = 90;
  const int MaxSpeed = 150;
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
    /* A note on vision coordinates
    Vision is configured for zero center mode.
    +Y = Down of center
    -Y = Up of center
    +X = Right of center
    -X = Left of center
    Top = 158
    Bottom = -158
    Right = 106
    Left = -106
    FOV Width = 316
    FOV Height = 212
    */
    //constants
    const int TOP_LIMIT = 158;
    const int BOTTOM_LIMIT = -158;
    const int RIGHT_LIMIT = 106;
    const int LEFT_LIMIT = -106;
    const int TOP_BOUND = TOP_LIMIT - 0;
    const int BOTTOM_BOUND = BOTTOM_LIMIT + 0;
    const int RIGHT_BOUND = RIGHT_LIMIT - 30;
    const int LEFT_BOUND = LEFT_LIMIT + 30;

    //target controller variables
    const int SAMPLE_SIZE = 6;

    //vision signatures
    const uint32_t RED_FLAG_SIG = 0;
    const uint32_t BLUE_FLAG_SIG = 1;

    //the dreaded sensor incarnate
    extern pros::Vision sensor;

    //initialize the vision sensor
    void Initialize();

    //vision object sorting algorithm
    bool VisionObjectSort(pros::vision_object_s_t r, pros::vision_object_s_t l);

    //vision sensor targeting controller
    void TargetingController();

    //flywheel speed controller
    void FlywheelController();
  }
}
