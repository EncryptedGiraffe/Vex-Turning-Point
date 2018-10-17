#include "main.h"
#include "controller.hpp"

//variables
int flippinCount = 0;

//controllers
pros::Controller* masterController = new pros::Controller(pros::E_CONTROLLER_MASTER);
pros::Controller* partnerControlle = new pros::Controller(pros::E_CONTROLLER_PARTNER);

//motors
namespace Motors
{
  //port variables
  const int driveLeftPort = 2;
  const int driveRightPort = 3;
  const int flywheelTopPort = 4;
  const int flywheelBottomPort = 5;
  const int armTopPort = 6;
  const int armBottomPort = 7;
  const int flippinPort = 8;
  const int intakePort = 9;

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
  pros::Motor* flywheelTop = new pros::Motor(flywheelTopPort, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
  //Flywheel bottom motor into Smart Port 5
  pros::Motor* flywheelBottom = new pros::Motor(flywheelBottomPort, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
  //arm top motor into Smart Port 6
  pros::Motor* armTop = new pros::Motor(armTopPort, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
  //arm bottom motor into Smart Port 7
  pros::Motor* armBottom = new pros::Motor(armBottomPort, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
  //flippin motor into Smart Port 8
  pros::Motor* flippin = new pros::Motor(flippinPort, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
  //intake motor into smart port 9
  pros::Motor* intake = new pros::Motor(intakePort, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
}

//flywheel controller
namespace Flywheel
{
  //max speed for the flywheel
  const int maxSpeed = 200;
  //speed
  int speed = 0;

  //flywheel controller
  void Controller()
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
}

namespace Drive
{
  void Tank(int leftSpeed, int rightSpeed)
  {
    //set the Motors
    Motors::driveLeft->move(leftSpeed);
    Motors::driveRight->move(rightSpeed);
  }
}

namespace Arm
{
  //arm position
  int position;

  //arm controller 0 = stay, 1 = up, -1 = down
  void Simple(int mode)
  {
    if(mode == 1)
    {
      //arm up
      Motors::armTop->move(127);
      Motors::armBottom->move(127);
    }
    else if(mode == -1)
    {
      //arm down
      Motors::armTop->move(-127);
      Motors::armBottom->move(-127);
    }
    else
    {
      //arm off
      Motors::armTop->move(0);
      Motors::armBottom->move(0);
    }
  }
}

namespace Flippin
{
  void Flip()
  {
    //increase flippin count
    flippinCount += 180;
  }
  void Controller()
  {
    //set the motor to the flippin count
    Motors::flippin->move_absolute(flippinCount, 200);
  }
}

namespace Intake
{
  //1 = forwards, 0 = stopped, -1 = backwards
  void Simple(int mode)
  {
    if(mode == 1)
    {
      //forwards
      Motors::intake->move(127);
    }
    else if(mode == -1)
    {
      //backwards
      Motors::intake->move(-127);
    }
    else
    {
      //stopped
      Motors::intake->move(0);
    }
  }
}
