#include "controller.hpp"

//variables
int flywheelSpeed = 0;
int flippinPosition = 0;

//controllers
okapi::Controller* masterController = new okapi::Controller(okapi::ControllerId::master);
okapi::Controller* partnerController = new okapi::Controller(okapi::ControllerId::partner);

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
  Mode mode = Stopped;
  int speed = 0;

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
  okapi::ChassisControllerIntegrated controller = okapi::ChassisControllerFactory::create(driveLeftPort, driveRightPort, AbstractMotor::gearset::green, {4_in, 12.7_in});
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
    Motors::armTop->move_absolute(position, 200);
    Motors::armBottom->move_absolute(position, 200);
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
  void Flip()
  {
    //increase the flippin position by 180
    flippinPosition += 180;
    //set to position
    Motors::flippin->move_absolute(flippinPosition, 150);
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
