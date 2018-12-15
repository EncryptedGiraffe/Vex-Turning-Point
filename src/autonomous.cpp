#include "controller.hpp"

void AutonomousStart()
{
  //set the flipper to rotate slightly
  Motors::flippin->move_absolute(100, 100);
  //wait for it to do so
  pros::delay(250);
  //set the flipper back to zero
  Motors::flippin->move_absolute(0, 100);
  //wait for it to do so
  pros::delay(250);
}

void autonomous()
{
  //start autonomous
  AutonomousStart();
}
