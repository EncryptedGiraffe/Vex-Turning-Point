#include "../include/controllers.hpp"

//controllers
Controller master = Controller(ControllerId::master);
Controller partner = Controller(ControllerId::partner);

namespace Robot
{
  Team_e_t team;
  StartingTile_e_t startingTile;
  uint32_t flagSig;
  bool IsCompetition;
}

namespace Motors
{
  //intake
  Motor intake = Motor(Ports::Intake, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
  //flipper
  Motor flipper = Motor(Ports::Flipper, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
}

namespace Chassis
{
  //closed and open loop control for chassis
  ChassisControllerIntegrated controller = ChassisControllerFactory::create({Ports::DriveLeftFront, Ports::DriveLeftBack}, {-Ports::DriveRightFront, -Ports::DriveRightBack});
}

namespace Intake
{
  ADIButton limit(Ports::IntakeSwitch);
  bool IsPressed = false;
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
        Motors::intake.move(-127);
      }
      else
      {
        Motors::intake.move(127);
      }
      //check if the limit switch has been hit
      if(limit.changedToPressed())
      {
        //stop the intake
        IsRunning = false;
      }
    }
    else
    {
      //turn off motor
      Motors::intake.move(0);
    }
  }
}

namespace Flywheel
{
  //velocity PID variables
  AsyncVelIntegratedController velController = AsyncControllerFactory::velIntegrated(Ports::Flywheel);
  //velocity management variables
  int _speed = 0;
  Mode mode = Variable;
  int speed = 0;

  void Controller()
  {
    switch(mode)
    {
      case Stopped:
        //check if the motors are stopped
        if(_speed > 20)
        {
          //lower the velocity by 1
          _speed -= 1;
        }
        else
        {
          //set the velocity to 0
          _speed = 0;
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
        _speed = speed;
        break;
    }
    //set the motors
    velController.setTarget(_speed);
    //Motors::flywheel->moveVelocity(flywheelSpeed);
  }
}

namespace Flipper
{
  bool IsFlipping = false;
  void StartUp()
  {
    //set the position of the motor to the lowered position
    Motors::flipper.move_absolute(Lowered, 100);
  }
  void RequestFlip()
  {
    //start flipping
    IsFlipping = true;
  }
  void Raise()
  {
    //set the flipper to the raised position
    Motors::flipper.move_absolute(Raised, MaxSpeed);
  }
  void Ramming()
  {
    //set the flipper to the ram position
    Motors::flipper.move_absolute(Ram, MaxSpeed);
  }
  void Controller()
  {
    //check if the flipper should be flipping
    if(IsFlipping)
    {
      //check if the flipper is in the raised position
      if(Motors::flipper.get_position() > (Raised-5) && Motors::flipper.get_position() < (Raised+5))
      {
        //lower the flipper
        Motors::flipper.move_absolute(Lowered, MaxSpeed);
        //done sending commands
        IsFlipping = false;
      }
      else
      {
        //raise the flipper
        Motors::flipper.move_absolute(Raised, MaxSpeed);
      }
    }
  }
}

namespace Sensors
{
  namespace Vision
  {
    //flag sig
    uint32_t flagSig;

    //the dreaded sensor itself
    pros::Vision sensor = pros::Vision(Ports::Vision);

    //init
    void Initialize()
    {
      //set the flag signature
      flagSig = static_cast<uint32_t>(Robot::team);
    }

    //sorting
    bool VisionObjectSort(pros::vision_object_s_t r, pros::vision_object_s_t l)
    {
      //return true if r goes before l
      return std::abs(r.x_middle_coord) < std::abs(l.x_middle_coord);
    }

    //targeting controller
    void TargetingController()
    {
      //create an array to hold the objects being read
      pros::vision_object_s_t objects_arr[SAMPLE_SIZE];
      //read the objects in
      sensor.read_by_sig(0, flagSig, SAMPLE_SIZE, objects_arr);
      //create a vector for the objects
      std::vector<pros::vision_object_s_t> objects_vec(objects_arr, objects_arr+SAMPLE_SIZE);
    }

    //flywheel speed controller
    void FlywheelController()
    {
      //set flywheel speed
      Flywheel::speed = Flywheel::speed;
    }
  }
}
