#include "controller.hpp"

//variables
ADIButton intakeSwitch(intakeLimitPort);

//controllers
Controller masterController(ControllerId::master);
//Controller partnerController(ControllerId::partner);

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
  pros::Motor* arm = new pros::Motor(armPort, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
  //flippin motor
  pros::Motor* flippin = new pros::Motor(flippinPort, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
  //intake motor
  pros::Motor* intake = new pros::Motor(intakePort, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
}

//flywheel controller
namespace Flywheel
{
  //velocity management variables
  int flywheelSpeed = 0;
  Mode mode = Variable;
  int speed = 0;

  //speeds
  int row = 0;
  bool isHighFlag = true;

  void SetSpeed()
  {
    //high or low?
    if(isHighFlag)
    {
      //set the flywheel speed
      speed = HighSpeeds[row];
    }
    else
    {
      //set the flywheel speed
      speed = LowSpeeds[row];
    }
  }

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
  ChassisControllerIntegrated controller = ChassisControllerFactory::create(driveLeftPort, driveRightPort, AbstractMotor::gearset::green, {4_in, 12.75_in});
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
    Motors::arm->move_absolute(position, 200);
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
      //rumble the controller
      masterController.rumble("..");
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

namespace Manager
{
  bool isStarted = false;

  void Manager()
  {
    //check if we have not started yet
    if(!isStarted)
    {
      //set the flipper to rotate slightly
      Motors::flippin->move_absolute(100, 100);
      //wait for it to do so
      while (!((Motors::flippin->get_position() < 105) && (Motors::flippin->get_position() > 95)))
      {
        //wait
        pros::delay(2);
      }
      //set the flipper back to zero
      Motors::flippin->move_absolute(0, 100);
      //wait for it to do so
      while (!((Motors::flippin->get_position() < 5) && (Motors::flippin->get_position() > -5)))
      {
        //wait
        pros::delay(2);
      }
      //hand control back to the flipper controllers
      isStarted = true;
      return;
    }

    //check for end-of-game controller rumble
    if(Time::gameTime > 95000 && Time::gameTime < 105000)
    {
      if(((Time::gameTime * 20) % 1000) == 0)
      {
        //10 seconds left
        //rumble controller
        masterController.rumble("-  ");
      }
    }

    //check for end-of-game flywheel spin-down
    if(Time::gameTime > 103000)
    {
      //shut down the flywheel
      Flywheel::mode = Flywheel::Stopped;
    }
  }
}
namespace Vision
{
  pros::Vision vision(visionPort);
}
