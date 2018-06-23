#include <main.h>
//variables
int flywheelSpeed = 0;
int flywheelStopCounter = 0;
bool isFlywheelStopping = false;
float lastFlywheelValue = 0;

void FlywheelDriver(int mode)
{
  switch (mode) {
    case -1:
      if(flywheelSpeed > flywheelStopThreshold)
      {
        flywheelSpeed -= 1;
      }
      else
      {
        flywheelSpeed = 0;
      }
      break;
    case 0:
      //stop
      isFlywheelStopping = true;
      break;
    case 1:
      //full power
      isFlywheelStopping = false;
      //set motors to full power
      flywheelSpeed = 127;
      break;
    case 2:
      //half power
      isFlywheelStopping = false;
      //check if spped is greater than half power
      if(flywheelSpeed > 63)
      {
        //slow down
        flywheelSpeed -= 1;
      }
      else if(flywheelSpeed < 63)
      {
        //speed up
        flywheelSpeed = 63;
      }
      break;
  }
  //flywheel stop check
  if(isFlywheelStopping)
  {
    //should we slow down or stop
    if(flywheelSpeed > 0)
    {
      //should for slow down or wait
      if(flywheelStopCounter == flywheelStopCount)
      {
        //slow down
        flywheelSpeed -= 1;
        flywheelStopCounter = 0;
      }
      else
      {
        flywheelStopCounter += 1;
      }
    }
    else
    {
      //stop
      flywheelSpeed = 0;
    }
  }
  //set all motors
  motorSet(motorFlywheelLeftTop, flywheelSpeed);
  motorSet(motorFlywheelLeftBottom, -flywheelSpeed);
  motorSet(motorFlywheelRightTop, -flywheelSpeed);
  motorSet(motorFlywheelRightBottom, flywheelSpeed);
}

float FlywheelRPS()
{
  //the revolutions per second
  float rps = 0;
  //the value of the encoder
  float encoder = encoderGet(flywheelEncoder);
  //calculate rps
  rps = ((((encoder - lastFlywheelValue) / 360) * 50) * flywheelSpeedRatio);
  //set last encoder value
  lastFlywheelValue = encoder;
  //return the result
  return rps;
}

void ArmDriver(int dir)
{
  int armSpeed = 0;

  if(dir == 1)
  {
    //go up
    armSpeed = 127;
  }
  else if(dir == -1)
  {
    //go down
    armSpeed = -127;
  }
  else
  {
    //stop
    armSpeed = 0;
  }

  //set motors
  motorSet(motorArmTop, -armSpeed);
  motorSet(motorArmBottom, -armSpeed);
}
