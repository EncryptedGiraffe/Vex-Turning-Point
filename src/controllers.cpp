#include "../include/controllers.hpp"

//controllers
Controller* master = new Controller(ControllerId::master);

namespace Motors
{
  //intake
  Motor* intake = new Motor(Ports::Intake, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
  //flipper
  Motor* flipper = new Motor(Ports::Flipper, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
}

namespace Chassis
{
  //closed and open loop control for chassis
  ChassisControllerIntegrated controller = ChassisControllerFactory::create({Ports::DriveLeftFront, Ports::DriveLeftBack}, {-Ports::DriveRightFront, -Ports::DriveRightBack});
}

namespace Intake
{
  bool IsRunning = false;
  bool IsBackwards = false;

  void Controller()
  {
    //check if the intake should be running
    if(IsRunning)
    {
      //turn on motor
      //check direction
      if(IsBackwards)
      {
        Motors::intake->move(-127);
      }
      else
      {
        Motors::intake->move(127);
      }
    }
    else
    {
      //turn off motor
      Motors::intake->move(0);
    }
  }
}

namespace Flywheel
{
  //velocity PID variables
  AsyncVelIntegratedController velController = AsyncControllerFactory::velIntegrated(Ports::Flywheel);
  //velocity management variables
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
        if(speed > MOTOR_GEARSET_06_MAXSPEED)
        {
          //set to limit
          speed = MOTOR_GEARSET_06_MAXSPEED;
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
    velController.setTarget(flywheelSpeed);
    //Motors::flywheel->moveVelocity(flywheelSpeed);
  }
}

namespace Flipper
{
  bool IsFlipping = false;
  void StartUp()
  {
    //set the position of the motor to the lowered position
    Motors::flipper->move_absolute(Lowered, 100);
  }
  void RequestFlip()
  {
    //start flipping
    IsFlipping = true;
  }
  void Raise()
  {
    //set the flipper to the raised position
    Motors::flipper->move_absolute(Raised, MaxSpeed);
  }
  void Ramming()
  {
    //set the flipper to the ram position
    Motors::flipper->move_absolute(Ram, MaxSpeed);
  }
  void Controller()
  {
    //check if the flipper should be flipping
    if(IsFlipping)
    {
      //check if the flipper is in the raised position
      if(Motors::flipper->get_position() > (Raised-2) && Motors::flipper->get_position() < (Raised+2))
      {
        //lower the flipper
        Motors::flipper->move_absolute(Lowered, MaxSpeed);
        //done sending commands
        IsFlipping = false;
      }
      else
      {
        //raise the flipper
        Motors::flipper->move_absolute(Raised, MaxSpeed);
      }
    }
  }
}
