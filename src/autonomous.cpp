#include "controller.hpp"

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

void autonomous()
{
  //rev up flywheel to shoot high flag
  Motors::flywheelTop->move(Flywheel::HighSpeeds[1]);
  Motors::flywheelBottom->move(Flywheel::HighSpeeds[1]);
  //wait for it to do so
  while (!((Motors::flywheelTop->get_actual_velocity() < Flywheel::HighSpeeds[1] + 10) && (Motors::flywheelTop->get_actual_velocity() > Flywheel::HighSpeeds[1] - 10)))
  {
    //wait
    pros::delay(2);
  }
  //run the intake to fire the ball
  Motors::intake->move_voltage(127);
  //wait for the ball to fire
  pros::delay(2000);
  //shut down intake
  Motors::intake->move_voltage(0);
  //drive forward 2 tiles to toggle low flag
  Drive::controller.moveDistance(48_in);
  //drive backwards 1 tile
  Drive::controller.moveDistance(24_in);
  //rotate 90 degrees right to face center of field
  Drive::controller.turnAngle(90_deg);
  //deploy the flipper
  DeployFlipper();
}
