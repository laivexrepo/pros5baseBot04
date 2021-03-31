#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "main.h"       // We need to include the PROS definitions

// We will use the globals.hpp include file to setup global variables, available
// throughout any program, or function.  This is done for conveinance so it is
// easier to track them.

#define DEBUG true      // GLobal DEBUG variable used to tun more verbose
                        // code on showing status of program

// ------------ make sure all motors are available to all code -------------
extern pros::Motor left_wheel;
extern pros::Motor right_wheel;

extern pros::Motor intake_motor;            // intake motor

// ----------- make sure the odometers are available to all code -----------
extern pros::Rotation left_odom;      // left side odometer
extern pros::Rotation right_odom;     // right side odometer

// ----------- declare soem global variables ------------------------------
extern int motorMaxSpeed;             // Maximum movement speed
extern const int motorDefaultSpeed;   // default movement speed we like
extern const int maxAllowedSpeed;     // a constant maximum allowed speed

#endif
