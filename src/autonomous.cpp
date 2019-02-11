#include "../include/controllers.hpp"

//function declarations
void Far();
void Close();

void autonomous()
{
  Robot::WriteMessage("Autonomous started!");
  //check which autonomous function to run
  if(Robot::startingTile == Robot::StartingTile_e_t::Close)
  {
    //close tile autonomous
    Close();
  }
  else
  {
    //far tile autonomous
    Far();
  }
  while(true)
  {
    pros::delay(20);
  }
}

void Close()
{
  //team check
  if(Robot::team == Robot::Red)
  {
    //////////Fire ball step//////////
    //set flywheel speed
    Flywheel::speed = 200;
    //run its controller to get to that speed
    Flywheel::Controller();
    //wait until it gets to that speed
    //Flywheel::velController.waitUntilSettled();
    pros::delay(3100);
    //run the intake to fire the ball
    Motors::intake.move(127);
    //wait for the ball to have time to fire
    pros::delay(1000);
    //shutdown the intake
    Motors::intake.move(0);
    //////////End of fire ball step///////////
    //////////Toggle low flag step////////////
    //turn counter clockwise
    Chassis::controller.turnAngle(-15);
    //drive forward 2 tiles which is 48 inches
    Chassis::controller.moveDistance(46_in);
    pros::delay(100);
    //turn counter clockwise
    Chassis::controller.turnAngle(-30);
    //drive backward 1 tile which is 24 inches
    Chassis::controller.moveDistance(-24_in);
    pros::delay(100);
    /////////End of toggle low flag step//////////
    /////////Flip first cap step//////////////////
    //deploy the flipper
    Flipper::StartUp();
    //rotate 90 degress clockwise
    Chassis::controller.turnAngle(90_deg);
    //drive forward a small amount
    //Chassis::controller.moveDistance(10_in);
    //start moving forward
    Chassis::controller.moveDistanceAsync(32_in);
    //give it time to move forward
    pros::delay(400);
    //raise the flipper
    Flipper::Raise();
    //wait for us to stop moving
    Chassis::controller.waitUntilSettled();
    //////////End of flip first cap step//////////
    //////////Platform parking step///////////////
    if(Robot::IsParking)
    {
      //rotate 90 degrees clockwise
      Chassis::controller.turnAngle(88_deg);
      //drive forward onto the platform
      Chassis::controller.moveDistance(58_in);
    }
    //////////End of platform parking step//////////
    /*
    //////////Flip second cap step//////////////////
    else
    {

    }
    */
    //////////End of flip second cap step//////////
    //////////Shutdown flywheel step///////////////
    //set flywheel to stopping
    Flywheel::mode = Flywheel::Stopped;
    //run the flywheel controller until the flywheel is stopped
    for(int i = 0; i < 200; ++i)
    {
      Flywheel::Controller();
      pros::delay(10);
    }
    //make sure it is stopped
    Flywheel::mode = Flywheel::Variable;
    Flywheel::speed = 0;
    Flywheel::Controller();
  }
  else
  {

  }

}

void Far()
{

}
