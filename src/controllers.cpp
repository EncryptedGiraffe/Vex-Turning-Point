#include "../include/controllers.hpp"

//controllers
Controller* master = new Controller(ControllerId::master);

namespace Motors
{
  //Flywheel
  Motor* flywheel = new Motor(Ports::Flywheel, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
  //intake
  Motor* intake = new Motor(Ports::Intake, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
}

namespace Chassis
{
  //closed and open loop control for chassis
  ChassisControllerIntegrated controller = ChassisControllerFactory::create({Ports::DriveLeftFront, Ports::DriveLeftBack}, {Ports::DriveRightFront, Ports::DriveRightBack});
}

namespace Intake
{
  bool IsRunning = false;

  void Controller()
  {
    //check if the intake should be running
    if(IsRunning)
    {
      //turn on motor
      Motors::intake->move_velocity(200);
    }
    else
    {
      //turn off motor
      Motors::intake->move_velocity(0);
    }
  }
}

namespace Flywheel
{
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
    Motors::flywheel->move_velocity(flywheelSpeed);
  }
}
