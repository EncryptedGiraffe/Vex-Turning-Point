#include "../include/controllers.hpp"

//variables
int turnDirection = 0;

//function declarations
void Far();
void Close();

void autonomous()
{
  Robot::WriteMessage("Autonomous started!");
  //check turn direction
  if(Robot::team == Robot::Team_e_t::Red)
  {
    //set rotation
    turnDirection = 1;
  }
  else
  {
    //set rotation
    turnDirection = -1;
  }
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
}

void Close()
{

}

void Far()
{

}
