#include "controller.hpp"

void autonomous()
{
  //run all controllers
  Manager::Manager();
  Time::Controller();
}
