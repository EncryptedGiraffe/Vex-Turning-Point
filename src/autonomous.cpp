#include "controller.hpp"

//variables
int flywheelSpeed = 0;

void DeployFlipper()
{
  //set the flipper to rotate slightly
  Motors::flippin->move_absolute(Flippin::startupFlipAmount, 100);
  //wait for it to do so
  while (!((Motors::flippin->get_position() < Flippin::startupFlipAmount + 5) && (Motors::flippin->get_position() > Flippin::startupFlipAmount - 5)))
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
}

void ShutdownFlywheel()
{
  for(int i = 0; i <= 200; ++i)
  {
    //check if the flywheel is spinning
    if(flywheelSpeed > 0)
    {
      //slow down flywheel
      flywheelSpeed -= 1;
      Motors::flywheelTop->move(flywheelSpeed);
      Motors::flywheelBottom->move(flywheelSpeed);
      //wait
      pros::delay(10);
    }
    else
    {
      //done
      break;
    }
  }
}

void autonomous()
{
  #ifdef AUTO_FAR
  //rev up flywheel to shoot high flag
  flywheelSpeed = Flywheel::HighSpeeds[3];
  Motors::flywheelTop->move(flywheelSpeed);
  Motors::flywheelBottom->move(flywheelSpeed);
  //wait for it to do so
  while (!((Motors::flywheelTop->get_actual_velocity() < Flywheel::HighSpeeds[3] + 10) && (Motors::flywheelTop->get_actual_velocity() > Flywheel::HighSpeeds[3] - 10)))
  {
    //wait
    pros::delay(2);
  }
  //run the intake to fire the ball
  Motors::intake->move_velocity(200);
  //wait for the ball to fire
  pros::delay(2000);
  //shut down intake
  Motors::intake->move_velocity(0);
  //shutdown the flywheel
  ShutdownFlywheel();
  /*
  //drive forward 2 tiles to toggle low flag
  Drive::controller.moveDistance(48_in);
  //drive backwards 1 tile
  Drive::controller.moveDistance(24_in);
  //rotate 90 degrees right to face center of field
  Drive::controller.turnAngle(90_deg);
  //deploy the flipper
  DeployFlipper();
  */
  #else
  //rev up flywheel to shoot high flag
  flywheelSpeed = Flywheel::HighSpeeds[1];
  Motors::flywheelTop->move(flywheelSpeed);
  Motors::flywheelBottom->move(flywheelSpeed);
  //wait for it to do so
  while (!((Motors::flywheelTop->get_actual_velocity() < Flywheel::HighSpeeds[1] + 10) && (Motors::flywheelTop->get_actual_velocity() > Flywheel::HighSpeeds[1] - 10)))
  {
    //wait
    pros::delay(2);
  }
  //run the intake to fire the ball
  Motors::intake->move_velocity(200);
  //wait for the ball to fire
  pros::delay(2000);
  //shut down intake
  Motors::intake->move_velocity(0);
  //shutdown the flywheel
  ShutdownFlywheel();
  //drive forward 2 tiles to toggle low flag
  Drive::controller.moveDistance(48_in);
  /*
  //drive backwards 1 tile
  Drive::controller.moveDistance(24_in);
  //rotate 90 degrees right to face center of field
  Drive::controller.turnAngle(90_deg);
  //deploy the flipper
  DeployFlipper();
  */
  #endif
}
