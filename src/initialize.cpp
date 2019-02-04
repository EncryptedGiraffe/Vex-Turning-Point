#include "../include/controllers.hpp"
#include "pros/apix.h"

//objects
lv_obj_t* title;
lv_obj_t* btnLeft;
lv_obj_t* btnLeftLabel;
lv_obj_t* btnRight;
lv_obj_t* btnRightLabel;
lv_obj_t* messages;

//button ID
const uint8_t btnLeftID = 1;
const uint8_t btnRightID = 2;

//positioning variables
const int titleX = 0;
const int titleY = -65;
const int btnLeftX = -100;
const int btnLeftY = 0;
const int btnRightX = 100;
const int btnRightY = 0;
const int messagesX = 0;
const int messagesY = 65;

//state variables
bool IsModeDone = false;
bool IsTeamDone = false;
bool IsTileDone = false;
bool IsInitDone = false;

//function declarations
lv_res_t Button_Click(lv_obj_t* btn);
void StartSelector();
void ModeSelector();
void TeamSelector();
void TileSelector();
void SelectorDone_Comp();
void SelectorDone_NoComp();

//functions
void Robot::WriteMessage(std::string message)
{
	//set the text
	lv_label_set_text(messages, message.c_str());
	//realign the text
	lv_obj_align(messages, NULL, LV_ALIGN_CENTER, messagesX, messagesY);
}
lv_res_t Button_Click(lv_obj_t* btn)
{
	//get the id of the button that was clicked
	uint8_t id = lv_obj_get_free_num(btn);
	//switch based on the button id
	switch(id)
	{
		case btnLeftID:
		{
			//check what script to run next
			if(IsModeDone)
			{
				if(IsTeamDone)
				{
					if(!IsTileDone)
					{
						//we are starting on the close tile
						Robot::startingTile = Robot::StartingTile::Close;
						//tile selection done
						IsTileDone = true;
						//done
						//fully initialized
						//check which done script to run
						if(Robot::IsCompetition)
						{
							SelectorDone_Comp();
						}
						else
						{
							SelectorDone_NoComp();
						}
					}
				}
				else
				{
					//we are on the red team
					Robot::team = Robot::Team::Red;
					//team selection done
					IsTeamDone = true;
					//find team
					TileSelector();
				}
			}
			else
			{
				//we are in competition mode
				Robot::IsCompetition = true;
				//mode selection done
				IsModeDone = true;
				//find team
				TeamSelector();
			}
			break;
		}
		case btnRightID:
		{
			//check what script to run next
			if(IsModeDone)
			{
				if(IsTeamDone)
				{
					if(!IsTileDone)
					{
						//we are starting on the close tile
						Robot::startingTile = Robot::StartingTile::Far;
						//tile selection done
						IsTileDone = true;
						//done
						//fully initialized
						//check which done script to run
						if(Robot::IsCompetition)
						{
							SelectorDone_Comp();
						}
						else
						{
							SelectorDone_NoComp();
						}
					}
				}
				else
				{
					//we are on the red team
					Robot::team = Robot::Team::Blue;
					//team selection done
					IsTeamDone = true;
					//find team
					TileSelector();
				}
			}
			else
			{
				//we are in competition mode
				Robot::IsCompetition = false;
				//mode selection done
				IsModeDone = true;
				//find team
				TeamSelector();
			}
			break;
		}
	}
	return LV_RES_OK;
}
void StartSelector()
{
	//create title
	title = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(title, "");

	//create message
	messages = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(messages, "");

	//create left button
	btnLeft = lv_btn_create(lv_scr_act(), NULL);
	//enable button resizing
	lv_cont_set_fit(btnLeft, true, true);
	//align the button and offset it
	lv_obj_align(btnLeft, NULL, LV_ALIGN_CENTER, btnLeftX, btnLeftY);
	//assign a id to the button
	lv_obj_set_free_num(btnLeft, btnLeftID);
	//set a click action to the buttton
	lv_btn_set_action(btnLeft, LV_BTN_ACTION_CLICK, Button_Click);

	//create a label for the button
	btnLeftLabel = lv_label_create(btnLeft, NULL);
	//set the test of the button label
	lv_label_set_text(btnLeftLabel, "Left");

	//create right button
	btnRight = lv_btn_create(lv_scr_act(), NULL);
	//enable button resizing
	lv_cont_set_fit(btnRight, true, true);
	//align the button and offset it
	lv_obj_align(btnRight, NULL, LV_ALIGN_CENTER, btnRightX, btnRightY);
	//assign a id to the button
	lv_obj_set_free_num(btnRight, btnRightID);
	//set a click action to the buttton
	lv_btn_set_action(btnRight, LV_BTN_ACTION_CLICK, Button_Click);

	//create a label for the button
	btnRightLabel = lv_label_create(btnRight, NULL);
	//set the test of the button label
	lv_label_set_text(btnRightLabel, "Right");
}

void ModeSelector()
{
	//set title text
	lv_label_set_text(title, "Competition Mode?");
	lv_obj_align(title, NULL, LV_ALIGN_CENTER, titleX, titleY);
	//set left button text
	lv_label_set_text(btnLeftLabel, "Yes");
	//set right button text
	lv_label_set_text(btnRightLabel, "No");
}

void TeamSelector()
{
	//set title text
	lv_label_set_text(title, "Team?");
	lv_obj_align(title, NULL, LV_ALIGN_CENTER, titleX, titleY);
	//set left button text
	lv_label_set_text(btnLeftLabel, "Red");
	//set right button text
	lv_label_set_text(btnRightLabel, "Blue");
}

void TileSelector()
{
	//set title text
	lv_label_set_text(title, "Tile?");
	lv_obj_align(title, NULL, LV_ALIGN_CENTER, titleX, titleY);
	//set left button text
	lv_label_set_text(btnLeftLabel, "Close");
	//set right button text
	lv_label_set_text(btnRightLabel, "Far");
}

void SelectorDone_Comp()
{
	//set title text
	std::string message;
	message.append("Robot configuration: Competition\n");
	if(Robot::team == Robot::Team::Red)
	{
		message.append("Team: Red\n");
	}
	else
	{
		message.append("Team: Blue\n");
	}
	if(Robot::startingTile == Robot::StartingTile::Close)
	{
		message.append("Starting Tile: Close\n");
	}
	else
	{
		message.append("Starting Tile: Far");
	}
	lv_label_set_text(title, message.c_str());
	lv_obj_align(title, NULL, LV_ALIGN_CENTER, titleX, titleY);
	//remove the buttons
	lv_label_set_text(btnLeftLabel, "");
	lv_label_set_text(btnRightLabel, "");
	lv_btn_set_state(btnRight, LV_BTN_STATE_INA);
	lv_btn_set_state(btnLeft, LV_BTN_STATE_INA);
	//init finished
	IsInitDone = true;
}

void SelectorDone_NoComp()
{
	//set title text
	std::string message;
	message.append("Robot configuration: General\n");
	if(Robot::team == Robot::Team::Red)
	{
		message.append("Team: Red\n");
	}
	else
	{
		message.append("Team: Blue\n");
	}
	if(Robot::startingTile == Robot::StartingTile::Close)
	{
		message.append("Starting Tile: Close\n");
	}
	else
	{
		message.append("Starting Tile: Far");
	}
	lv_label_set_text(title, message.c_str());
	lv_obj_align(title, NULL, LV_ALIGN_CENTER, titleX, titleY);
	//remove the buttons
	lv_label_set_text(btnLeftLabel, "");
	lv_label_set_text(btnRightLabel, "");
	lv_btn_set_state(btnRight, LV_BTN_STATE_INA);
	lv_btn_set_state(btnLeft, LV_BTN_STATE_INA);
	//init finished
	IsInitDone = true;
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	//configure vision sensor
	Sensors::Vision::sensor.set_zero_point(pros::E_VISION_ZERO_CENTER);
	//draw initial screen
	StartSelector();
	//is in competition mode?
	ModeSelector();

	//wait until selector is done
	while(!IsInitDone)
	{
		delay(20);
	}
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{

}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize()
{
	//write a message
	Robot::WriteMessage("Waiting for game to start...");
}
