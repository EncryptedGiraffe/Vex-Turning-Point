#include "main.h"
#include "controller.hpp"

//variables
int flywheelSpeed = 0;

//controllers
pros::Controller* masterController = new pros::Controller(pros::E_CONTROLLER_MASTER);
pros::Controller* partnerController = new pros::Controller(pros::E_CONTROLLER_PARTNER);

//motors
namespace Motors
{
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
  Speeds speed = Stopped;
  int variableSpeed = 0;

  void Controller()
  {
    switch(speed)
    {
      case Stopped:
        //check if the motors are stopped
        if(flywheelSpeed > 20)
        {
          //lower the velocity by 1
          flywheelSpeed -= 1;
        }
        else
        {
          //set the velocity to 0
          flywheelSpeed = 0;
        }
        break;
      case Max:
        //set motors to full power
        flywheelSpeed = MOTOR_GEARSET_18_MAXSPEED;
        break;
      case Variable:
        //upper bounds checking
        if(variableSpeed > MOTOR_GEARSET_18_MAXSPEED)
        {
          //set to limit
          variableSpeed = MOTOR_GEARSET_18_MAXSPEED;
        }
        //lower bounds checking
        if(variableSpeed < 0)
        {
          //set to limit
          variableSpeed = 0;
        }
        //set speed to variableSpeed
        flywheelSpeed = variableSpeed;
        break;
    }
    //set the motors
    Motors::flywheelTop->move_velocity(flywheelSpeed);
    Motors::flywheelBottom->move_velocity(flywheelSpeed);
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
  void Arcade(int speed, int rotate)
  {
    //set the motors
    Motors::driveLeft->move(speed - rotate);
    Motors::driveRight->move(speed + rotate);
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
    //flip by 180 degrees
    Motors::flippin->move_absolute(180, 200);
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
