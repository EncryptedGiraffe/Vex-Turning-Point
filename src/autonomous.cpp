#include "controller.hpp"

void autonomous()
{
  //rev up flywheel
  Motors::flywheelTop->move_velocity(Flywheel::HighSpeeds[3]);
  Motors::flywheelBottom->move_velocity(Flywheel::HighSpeeds[3]);
  //wait for it to speed up
  pros::delay(3000);
  //turn on the intake to feed the ball into the flywheel
  Motors::intake->move(127);
  //wait for the ball to fire
  pros::delay(3000);
  //slow down the flywheel
  Motors::flywheelTop->move_velocity(120);
  Motors::flywheelBottom->move_velocity(120);
  pros::delay(500);
  Motors::flywheelTop->move_velocity(100);
  Motors::flywheelBottom->move_velocity(100);
  pros::delay(500);
  Motors::flywheelTop->move_velocity(80);
  Motors::flywheelBottom->move_velocity(80);
  pros::delay(500);
  Motors::flywheelTop->move_velocity(60);
  Motors::flywheelBottom->move_velocity(60);
  pros::delay(500);
  Motors::flywheelTop->move_velocity(40);
  Motors::flywheelBottom->move_velocity(40);
  pros::delay(500);
  Motors::flywheelTop->move_velocity(20);
  Motors::flywheelBottom->move_velocity(20);
  pros::delay(500);
  Motors::flywheelTop->move_velocity(0);
  Motors::flywheelBottom->move_velocity(0);
  pros::delay(500);
}
