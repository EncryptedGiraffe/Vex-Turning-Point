#include "../include/controllers.hpp"

//function declarations
void Far();
void Close();
void Skills();

void autonomous()
{
  Robot::WriteMessage("Autonomous started!");
  //check if skills
  if(Robot::IsSkills)
  {
    Skills();
    return;
  }
  //check which autonomous function to run
  if(Robot::startingTile == Robot::StartingTile_e_t::Close)
  {
    //close tile autonomous
    Close();
    return;
  }
  else
  {
    //far tile autonomous
    Far();
    return;
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
    Chassis::controller.turnAngle(-7);
    pros::delay(100);
    //drive forward 2 tiles which is 48 inches
    Chassis::controller.moveDistance(48_in);
    pros::delay(100);
    //turn counter clockwise
    Chassis::controller.turnAngle(-20_deg);
    pros::delay(100);
    //drive backward 1 tile which is 24 inches
    Chassis::controller.moveDistance(-24_in);
    pros::delay(100);
    /////////End of toggle low flag step//////////
    /////////Flip first cap step//////////////////
    //deploy the flipper
    Flipper::StartUp();
    //rotate 90 degress clockwise
    Chassis::controller.turnAngle(96_deg);
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
      Chassis::controller.turnAngle(94_deg);
      //drive forward onto the platform
      Chassis::controller.moveDistance(60_in);
    }
    //////////End of platform parking step//////////
    //////////Flip second cap step//////////////////
    else
    {

    }
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
    //turn clockwise
    Chassis::controller.turnAngle(16_deg);
    pros::delay(100);
    //drive forward 2 tiles which is 48 inches
    Chassis::controller.moveDistance(48_in);
    pros::delay(100);
    //turn counter clockwise
    Chassis::controller.turnAngle(20_deg);
    pros::delay(100);
    //drive backward 1 tile which is 24 inches
    Chassis::controller.moveDistance(-24_in);
    pros::delay(100);
    /////////End of toggle low flag step//////////
    /////////Flip first cap step//////////////////
    //deploy the flipper
    Flipper::StartUp();
    //rotate counter clockwise
    Chassis::controller.turnAngle(-90_deg);
    //drive forward a small amount
    //Chassis::controller.moveDistance(10_in);
    //start moving forward
    Chassis::controller.moveDistanceAsync(35_in);
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
      //rotate counter clockwise
      Chassis::controller.turnAngle(-92_deg);
      //drive forward onto the platform
      Chassis::controller.moveDistance(57_in);
    }
    //////////End of platform parking step//////////
    //////////Flip second cap step//////////////////
    else
    {

    }
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

}

void Far()
{
  //check team
  if(Robot::team == Robot::Red)
  {
    //rev up flywheel to shoot high middle flag
    Flywheel::speed = 142;
    //apply it
    Flywheel::Controller();
    //allow the flywheel to get to the velocity
    //Flywheel::velController.waitUntilSettled();
    pros::delay(2700);
    //run the intake to fire the ball
    Motors::intake.move(127);
    //wait for the ball to fire
    pros::delay(1000);
    //stop the intake
    Motors::intake.move(0);
    //rotate clock wise
    Chassis::controller.turnAngle(68_deg);
    //deploy flipper
    Flipper::StartUp();
    //drive forward
    Chassis::controller.moveDistance(32_in);
    //rotate counter clockwise
    Chassis::controller.turnAngle(-25_deg);
    //rotate clockwise
    Chassis::controller.turnAngle(72_deg);
    //drive forward
    Chassis::controller.setMaxVelocity(100);
    Chassis::controller.moveDistanceAsync(12_in);
    //wait for it to move
    pros::delay(700);
    //raise the flipper
    Flipper::Raise();

    //Shutdown flywheel
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
    Chassis::controller.setMaxVelocity(200);
  }
  else
  {
    //rev up flywheel to shoot high middle flag
    Flywheel::speed = 142;
    //apply it
    Flywheel::Controller();
    //allow the flywheel to get to the velocity
    //Flywheel::velController.waitUntilSettled();
    pros::delay(2700);
    //run the intake to fire the ball
    Motors::intake.move(127);
    //wait for the ball to fire
    pros::delay(1000);
    //stop the intake
    Motors::intake.move(0);
    //rotate clock wise
    Chassis::controller.turnAngle(-68_deg);
    //deploy flipper
    Flipper::StartUp();
    //drive forward
    Chassis::controller.moveDistance(32_in);
    //rotate counter clockwise
    Chassis::controller.turnAngle(25_deg);
    //rotate clockwise
    Chassis::controller.turnAngle(-72_deg);
    //drive forward
    Chassis::controller.setMaxVelocity(100);
    Chassis::controller.moveDistanceAsync(12_in);
    //wait for it to move
    pros::delay(700);
    //raise the flipper
    Flipper::Raise();

    //Shutdown flywheel
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
    Chassis::controller.setMaxVelocity(200);
  }
}

void Skills()
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
  pros::delay(100);
  //drive forward 2 tiles which is 48 inches
  Chassis::controller.moveDistance(50_in);
  pros::delay(100);
  //turn counter clockwise
  Chassis::controller.turnAngle(-10_deg);
  pros::delay(100);
  //drive backward 1 tile which is 24 inches
  Chassis::controller.moveDistance(-24_in);
  pros::delay(100);
  /////////End of toggle low flag step//////////
  /////////Flip first cap step//////////////////
  //deploy the flipper
  Flipper::StartUp();
  //rotate 90 degress clockwise
  Chassis::controller.turnAngle(88_deg);
  //drive forward a small amount
  //Chassis::controller.moveDistance(10_in);
  //start moving forward
  Chassis::controller.moveDistance(12_in);
  //raise the flipper
  Flipper::Raise();
  //////////End of flip first cap step//////////
  //rotate clockwise
  Chassis::controller.turnAngle(90_deg);
  //lower the flipper
  Flipper::StartUp();
  //drive forward
  Chassis::controller.moveDistance(24_in);
  //rotate counter clock wise
  Chassis::controller.turnAngle(-105_deg);
  //drive forward
  Chassis::controller.moveDistance(12_in);
  //rotate clockwise
  Chassis::controller.turnAngle(15_deg);
  //drive backward
  Chassis::controller.moveDistance(-36_in);
  //drive forward
  Chassis::controller.moveDistance(4_in);
  //rotate clockwise
  Chassis::controller.turnAngle(90_deg);
  //drive forward
  Chassis::controller.moveDistance(24_in);
  //rotate counter clockwise
  Chassis::controller.turnAngle(-90_deg);
  //drive onto the center platform
  Chassis::controller.moveDistance(54);
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
