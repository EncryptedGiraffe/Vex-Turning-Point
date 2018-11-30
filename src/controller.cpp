#include "controller.hpp"

//variables
okapi::ADIButton intakeSwitch(intakeLimit);

//controllers
okapi::Controller masterController(okapi::ControllerId::master);
//okapi::Controller partnerController(okapi::ControllerId::partner);

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
  //Flywheel top motor
  pros::Motor* flywheelTop = new pros::Motor(flywheelTopPort, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
  //Flywheel bottom motor
  pros::Motor* flywheelBottom = new pros::Motor(flywheelBottomPort, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
  //arm top motor
  pros::Motor* armTop = new pros::Motor(armTopPort, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
  //arm bottom motor
  pros::Motor* armBottom = new pros::Motor(armBottomPort, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
  //flippin motor
  pros::Motor* flippin = new pros::Motor(flippinPort, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
  //intake motor
  pros::Motor* intake = new pros::Motor(intakePort, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
}

//flywheel controller
namespace Flywheel
{
  int flywheelSpeed = 0;
  Mode mode = Variable;
  int speed = 0;

  void Controller()
  {
    switch(mode)
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
      case Variable:
        //upper bounds checking
        if(speed > MOTOR_GEARSET_18_MAXSPEED)
        {
          //set to limit
          speed = MOTOR_GEARSET_18_MAXSPEED;
        }
        //lower bounds checking
        if(speed < 0)
        {
          //set to limit
          speed = 0;
        }
        //set speed to variableSpeed
        flywheelSpeed = speed;
        break;
    }
    //set the motors
    Motors::flywheelTop->move_velocity(flywheelSpeed);
    Motors::flywheelBottom->move_velocity(flywheelSpeed);
  }
}

namespace Drive
{
  okapi::ChassisControllerIntegrated controller = okapi::ChassisControllerFactory::create(driveLeftPort, driveRightPort, okapi::AbstractMotor::gearset::green, {1128, 3.125});
}

namespace Arm
{
  //arm position
  int position;

  //arm controller
  void Controller()
  {
    //make sure the position is within bounds
    if(position > UpperBound)
      //set position to upper bound
      position = UpperBound;
    if(position < LowerBound)
      //set position to lower bound
      position = LowerBound;

    //set motors to the position
    Motors::armTop->move_absolute(position, 100);
    Motors::armBottom->move_absolute(position, 100);
  }

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
  int flippinPosition = 0;
  int flippinTimeout = 0;
  bool isFlippin = false;
  void Flip()
  {
    if(isFlippin == false)
    {
      //now flippin
      isFlippin = true;
      //set timeout
      flippinTimeout = Time::gameTime;
    }
  }

  void Controller()
  {
    if(isFlippin)
    {
      if(Time::gameTime - flippinTimeout == 20)
      {
        //raise arm
        Arm::position += 50;
      }
      if(Time::gameTime - flippinTimeout == 300)
      {
        //increase the flippin position by 180
        flippinPosition += 180;
        //set to position
        Motors::flippin->move_absolute(flippinPosition, 150);
      }
      if(Time::gameTime - flippinTimeout == 600)
      {
        //drop the arm
        Arm::position -= 50;
      }
      if(Time::gameTime - flippinTimeout == 900)
      {
        //done
        isFlippin = false;
      }
    }
  }
}

namespace Intake
{
  bool running = false;

  void Controller()
  {
    //check if the limit switch has been hit
    if(intakeSwitch.changedToPressed())
    {
      //stop
      running = false;
    }
    if(running)
    {
      //run motor
      Motors::intake->move(127);
    }
    else
    {
      //stop motor
      Motors::intake->move(0);
    }
  }
}

namespace Time
{
  int gameTime = 0;

  void Controller()
  {
    gameTime += 20;
  }
}
