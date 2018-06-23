#ifndef DRIVERS_H
#define DRIVERS_H

#include <main.h>

//Controls the flywheel - mode: 0 = stop, 1 = full power, 2 = half power
void FlywheelDriver(int mode);

//measures the flywheel's revolutions per second
float FlywheelRPS();

//simple controller for testing the arm
void ArmDriver(int dir);

#endif
