#ifndef VARIABLES_H
#define VARIABLES_H

#include <main.h>

//motors
#define motorFlywheelLeftTop 2 //flywheel left tower top motor
#define motorFlywheelLeftBottom 3 //flywheel left tower bottom motor
#define motorFlywheelRightTop 8 //flywheel right tower top motor
#define motorFlywheelRightBottom 9 //flywheel right tower bottom motor
#define motorArmTop 4 //the upper motor of the main arm
#define motorArmBottom 5 //the lower motor of the main arm

//motor speeds
#define speedArm 1.0 //speed of the main arm

//sensors
#define flywheelEncoderTop 1 //flywheel optical shaft encoder top port into digital 1
#define flywheelEncoderBottom 2 //flywheel optical shaft encoder bootom port into digital 2
Encoder flywheelEncoder; //the optical shaft encoder for the flywheel

//other variables
#define flywheelStopThreshold 5 //how slow should the flywheel go before stopping completely
#define flywheelStopCount 2 //how slow should the flywheel slow down
#define flywheelSpeedRatio 11.666666 //what is the flywheel's speed advantage, used for caluclating rps

#endif
