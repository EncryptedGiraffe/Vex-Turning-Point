#include "main.h"
#include "controller.hpp"

////////////////////Variable definitions////////////////////

//controllers
okapi::Controller* masterController = new okapi::Controller(okapi::ControllerId::master);
okapi::Controller* partnerController = new okapi::Controller(okapi::ControllerId::partner);

//motors
namespace Motors
{
  //port variables
  const int driveLeftPort = 2;
  const int driveRightPort = 3;
  const int flywheelTopPort = 4;
  const int flywheelBottomPort = 5;

  /*
  Format:
  pros::Motor* ?name? = new pros::Motor(?smart port?, pros::E_MOTOR_GEARSET_18, ?reversed?, pros::E_MOTOR_ENCODER_DEGREES);
  Gearsets:
  E_MOTOR_GEARSET_36,	36:1, 100 RPM, Red gear set
  E_MOTOR_GEARSET_18, 18:1, 200 RPM, Green gear set
  E_MOTOR_GEARSET_06, 6:1, 600 RPM, Blue Gear Set
  */
  //Drive Chassis left motor into Smart Port 2
  pros::Motor* driveLeft = new pros::Motor(driveLeftPort, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
  //Drive Chassis right motor into Smart Port 3
  pros::Motor* driveRight = new pros::Motor(driveRightPort, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
  //Flywheel top motor into Smart Port 4
  pros::Motor* flywheelTop = new pros::Motor(flywheelTopPort, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
  //Flywheel bottom motor into Smart Port 5
  pros::Motor* flywheelBottom = new pros::Motor(flywheelBottomPort, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
}

//flywheel controller
namespace Flywheel
{
  //max speed for the flywheel
  const int maxSpeed = 200;
  //speed
  int speed = 0;
}

namespace Drive
{
  okapi::ChassisControllerIntegrated driveController = okapi::ChassisControllerFactory::create(Motors::driveLeftPort, Motors::driveRightPort, okapi::AbstractMotor::gearset::green);
}

namespace Arm
{
  //arm position
  int position;
}

////////////////////Function definition////////////////////
//flywheel controller
void FlywheelController()
{
  //check if requested speed is greater than max maxSpeed
  if(Flywheel::speed > Flywheel::maxSpeed)
  {
    //set the speed to max maxSpeed
    Flywheel::speed = Flywheel::maxSpeed;
  }
  //set the flywheel motors to the requested speed
  Motors::flywheelTop->move_velocity(Flywheel::speed);
  Motors::flywheelBottom->move_velocity(Flywheel::speed);
}
